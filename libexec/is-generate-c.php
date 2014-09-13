#!/usr/bin/php
<?php

$srcdir = getcwd(). "/.src/";
@mkdir($srcdir);

$ssource=$argv[1];
$csource= $srcdir . str_replace('.is', '.c', $ssource);

$modulesIndex = array();
$modulesInitializers = array();
$modulesInitialized = array();
$inBlock = false;
$offset = "";
$entryPoint = '';
$localVariables = array();
global $iterator;
global $modulesInitialized;
global $modulesIndex;
global $modulesInitializers;
$iterator=1000;


function initializeModule($module) {
    global $modulesInitialized;
    global $modulesIndex;
    global $modulesInitializers;
    global $iterator;

    $modulesInitialized[$module] = true;

    if (!isset($modulesInitializers[$module])) {
        return array($modulesIndex[$module] , " (" . $modulesIndex[$module] . "*) " . $modulesIndex[$module] . "::getInstance();\n");
    }
    $rmodule = $modulesInitializers[$module];
    list($class, $code) = initializeModule($rmodule);
    echo " $class *{$class}_local = $code\n";
    return array($modulesIndex[$module], " (" . $modulesIndex[$module] . "*) " . $modulesIndex[$module] . "::getInstance({$class}_local);\n");
}

function BadExpression($expression, $detail1) {
    error_log( "	BAD EXPRESSION: \n		ROW:	$expression\n		DETAIL:	$detail1\n\n\n", 3, 'php://stderr');
    exit(1);
}

function factoryExpression($expression) {
    global $iterator;
    if (preg_match('/^("[^"]*")$/',$expression, $matches)) { //string (without excapeing)
	$rr = end($matches);
	$varc = 'var_'.$iterator;
	$iterator++;
	$var = 'var_'.$iterator;
	$iterator++;
	$localVariables []= $var;
	$localVariables []= $varc;
	return array($var, "char {$varc}[] = $rr;
bitPack *$var = new bitPack();
{$var}->len = (strlen($varc)+1)*sizeof(char);
{$var}->bytes = new char [{$var}->len];
strcpy({$var}->bytes, $varc);\n");
    }
    BadExpression($expression);
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
	$required = end($required); // "cli as c" or "cli" or "cli(<inh) as c"
	if (preg_match('/^([A-z0-9\-\_]+)\(<(.*)\)\s+as\s+([A-z0-9\-\_]+)$/', $required, $matches)) { // "cli(<inheirt) as c"
	    $module = $matches[1];
	    $name = $matches[3];
	    $modulesIndex[$name] = $module;
	    $modulesInitializers[end($matches)] = $matches[2];
	} else if (preg_match('/^([A-z0-9\-\_]+)\s+as\s+([A-z0-9\-\_]+)$/', $required, $matches)) { // "cli as c"
	    $module = $matches[1];
	    $name = $matches[2];
	    $modulesIndex[$name] = $module;
	} else if (preg_match('/^([A-z0-9\-\_]+)$/', $required, $matches)) { // "cli"
	    $module = end($matches);
	    $modulesIndex[$module] = $module;
	} else {
	    BadExpression($row, $required);
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
		
		list($class, $code) = initializeModule($module);
		echo $offset . " $class *{$class}_local = $code\n";
	    }
	}
	
//    echo $offset . $modulesIndex[$module] . "* ". $modulesIndex[$module] . "_local = (".$modulesIndex[$module]."*)" . $modulesIndex[$module] . "::getInstance($parentVar);\n";
	
	
	//initialize expression
	list($varName, $printable) = factoryExpression($expression);
	echo $printable;
	
	//run command
	switch ($command) {
	    case '<': //cout
		echo $offset .  $modulesIndex[$module] . "_local->cout($varName);\n";
		break;
	    case '>': //cin
		echo $offset .  "$varName = " . $modulesIndex[$module] . "_local->cin();\n";
		break;
	}
//	var_dump($module, $command, $expression);
	continue;
    }

    echo $row . "\n";
}
