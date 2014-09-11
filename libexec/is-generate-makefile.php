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
    if (preg_match('/^[A-z0-9_-]{3,}$/', $name)) {
	return $name;
    }
    doerror("bad provide name:" . $name);
    return null;
}

$source = $argv[1];
$csource = str_replace('.is', '.cpp', $source);
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
		if (preg_match('/^as\s+([A-z0-9_-]+)$/', $args, $aliasMatches)) {
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
$topdo = "";
$requires_make = "";
$requires = "";
$includes = "";

foreach ($state['required'] as $name => $realnamear) {
    list($realname) = $realnamear;
    if (
        file_exists($modules.DIRECTORY_SEPARATOR.$realname)
       ) {
	$topdo .= "	mkdir -p .obj/modules/$realname\n";
	$c_list = popen("ls -1 $modules/$realname/.module/*.o | grep -v is-cc-module.o", 'r');
	while (($c_file = trim(fgets($c_list))) != false){
//	    echo $c_file . "\n";
	    if (basename($c_file) != ($realname . ".cpp")) {
		$o_file = basename($c_file);
		$requires_make .= "	cp $c_file .obj/modules/$realname/$o_file\n";
		$requires .= " .obj/modules/$realname/$o_file";
	    }
	}
	pclose($c_list);
	$h_file = "$modules/$realname/$realname.hpp";
	$topdo .= "	cp $h_file .obj/modules/$realname/\n";
	$includes .= " -I.obj/modules/$realname/";
    } else {
	doerror("Unknown include: " . $realname);
    }
}

$globalh = __DIR__ . "/../include/";
$includes .= " -I$globalh";

if (count($errors) > 0) {
    foreach ($errors as $error) {
	echo $error . "\n";
    }
    exit(1);
}

$makefilename = $argv[2];
$makefile = "\n\nall:\n";
$makefile .= "	mkdir -p .obj/\n";
$makefile .= $topdo;
$makefile .= "	g++ -O2 $includes -c .src/$csource -o .obj/$coutput\n";
$makefile .= $requires_make;
$makefile .= "	g++ -O2 $includes .obj/$coutput $requires -o $outname\n\n";
$makefile .= "clean:\n";
$makefile .= "	rm -rf .obj/\n";

file_put_contents($makefilename, $makefile);

exit(0);
