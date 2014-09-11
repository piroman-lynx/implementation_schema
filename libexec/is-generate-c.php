#!/usr/bin/php
<?php

$srcdir = getcwd(). "/.src/";
@mkdir($srcdir);

$ssource=$argv[1];
$csource= $srcdir . str_replace('.is', '.c', $ssource);

$modulesIndex = array();
$modulesInitialized = array();
$inBlock = false;
$offset = "";
$entryPoint = '';
$localVariables = array();

function factoryExpression($expression) {
    if (preg_match('/^("[^"]*")$/',$expression, $matches)) { //string (without excapeing)
	return array(end($matches), "");
    }
    throw new BadExpression($expression);
}

$source = preg_split('/[\r\n]/', file_get_contents($ssource));
foreach ($source as $row) {
    $row = trim($row);

    //provide
    if (preg_match('/^#provide\s+(binary|library)\s+([A-z0-9\-\_]+)/', $row, $matches)) {
	if ($matches[1] == 'binary') {
	    $entryPoint = trim($matches[2]);
	}
	continue;
    }
    
    //require
    if (preg_match('/^#require\s+(.*)$/', $row, $required)) {
	$required = end($required); // "cli as c" or "cli"
	if (preg_match('/^([A-z0-9\-\_]+)\s+as\s+([A-z0-9\-\_]+)$/', $required, $matches)) { // "cli as c"
	    $module = $matches[1];
	    $name = $matches[2];
	    $modulesIndex[$name] = $module;
	} else if (preg_match('/^([A-z0-9\-\_]+)$/', $required, $matches)) { // "cli"
	    $module = end($matches);
	    $modulesIndex[$module] = $module;
	} else {
	    badExpression($row, $required);
	}
	echo "#include \"$module.hpp\"\n";
	continue;
    }

    //block, for example "hello_world {"
    if (preg_match('/([A-z0-9\-\_]+)\s+{$/', $row, $matches)) {
	//var_dump($matches);
	$block = trim(end($matches));
	if ($entryPoint == $block) {
	    echo "int main(int argc, char* argv[]) {\n";
	}
	$inBlock = true;
	$offset .= "  ";
	continue;
    }

    if (trim($row) == "}") {
	$inBlock = false;
	$modulesInitialized[$module] = array();
	$offset = substr($offset, 0, strlen($offset)-2);
	echo "}\n";
	continue;
    }

    //module operators
    if (preg_match('/^([A-z0-9\-\_]+)\s*(<|>)\s*(.*)$/', $row, $matches)) {
	$module = trim($matches[1]);
	$command = trim($matches[2]);
	$expression = trim($matches[3]);
	
	if (isset($modulesIndex[$module])) {
	    if (empty($modulesInitialized[$module])) {
		$modulesInitialized[$module] = true;
		echo $offset . $modulesIndex[$module] . "_local = " . $modulesIndex[$module] . "::getInstance();\n";
	    }
	}
	
	//initialize expression
	list($varName, $printable) = factoryExpression($expression);
	echo $printable;
	
	//run command
	switch ($command) {
	    case '<': //cout
		echo $offset .  $modulesIndex[$module] . "_local.cout($varName);\n";
		break;
	    case '>': //cin
		echo $offset .  "$varName = " . $modulesIndex[$module] . "_local.cin();\n";
		break;
	}
//	var_dump($module, $command, $expression);
	continue;
    }

    echo $row . "\n";
}

