#!/usr/bin/php
<?php

$state = array(
    'provide'=>null,
    'provide_name'=>null,
    'required' => array(),
);

$errors = array();

function doerror($error) {
    global $errors;
    $errors []= $error;
}

function validate_provide($provide){
    if (preg_match('/^(binary|library)$/', $provide)) {
	return $provide;
    }
    doerror("bad provide value: " . $provide);
    return null;
}

function validate_provide_name($name) {
    if (preg_match('/^[A-z0-9_]{3,}$/', $name)) {
	return $name;
    }
    doerror("bad provide name:" . $name);
    return null;
}

$source = $argv[1];
$csource = str_replace('.is', '.c', $source);
$coutput = str_replace('.is', '.o', $source);
$outname = str_replace('.is', '.out', $source);

$f = fopen($source, "r");
while (($buffer = fgets($f)) !== false) {
    $buffer = trim($buffer);
    if (preg_match("/^\#([A-z]+)\s+([A-z0-9]+)\s*(.*)$/", $buffer, $matches)) {
	list($all, $directive, $value, $args) = $matches;
	switch ($directive) {
	    case 'provide':
		$state['provide'] = validate_provide($value);
		$state['provide_name'] = validate_provide_name($args);
		break;
	    case 'require':
		if (preg_match('/^as\s+([A-z0-9_]+)$/', $args, $aliasMatches)) {
		    if (isset($state['required'][$aliasMatches[1]])) {
			doerror("Duplicate require: " . $aliasMatches[1] );
			break;
		    }
		    $state['required'][$aliasMatches[1]] = array($value);
		} else {
		    if (isset($state['required'][$value])) {
			doerror("Duplicate require: " . $value);
			break;
		    }
		    $state['required'][$value] = array($value);
		}
		break;
	}
    }
}

$checkList = array('provide', 'provide_name');
foreach ($checkList as $one) {
    if (empty($state[$one])) {
	doerror("Empty " . $one);
    }
}

$modules = getcwd() . "/" . ".is/modules/";
$requires_make = "";
$requires = "";

foreach ($state['required'] as $name => $realnamear) {
    list($realname) = $realnamear;
    if (
        file_exists($modules.DIRECTORY_SEPARATOR.$realname)
       ) {
	$requires_make .= "	mkdir -p .obj/modules/$realname\n";
	$c_list = popen("ls -1 $modules/$realname/*.c", 'r');
	while (($c_file = trim(fgets($c_list))) != false){
	    if (basename($c_file) != ($realname . ".c")) {
		$o_file = str_replace('.c', '.o', basename($c_file));
		$requires_make .= "	gcc -O2 -c $c_file -o .obj/modules/$realname/$o_file\n";
		$requires .= " .obj/modules/$realname/$o_file";
	    }
	}
	pclose($c_list);
    } else {
	doerror("Unknown include: " . $realname);
    }
}

if (count($errors) > 0) {
    foreach ($errors as $error) {
	echo $error . "\n";
    }
    exit(1);
}

$makefilename = $argv[2];
$makefile = "all:\n";
$makefile .= "	mkdir -p .obj/\n";
$makefile .= "	gcc -O2 -c .src/$csource -o .obj/$coutput\n";
$makefile .= $requires_make;
$makefile .= "	gcc -O2 .obj/$coutput $requires -o .obj/$outname\n\n";
$makefile .= "clean:\n";
$makefile .= "	rm -rf .obj/\n";

file_put_contents($makefilename, $makefile);

exit(0);
