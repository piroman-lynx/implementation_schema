#!/usr/bin/php
<?php

$srcdir = getcwd(). "/.src/";
@mkdir($srcdir);

$ssource=$argv[1];
$csource= $srcdir . str_replace('.is', '.c', $ssource);

$state = array(
    'required' => array(),
);

$build_index_list = explode("\n", file_get_contents(getcwd()."/.is/build_index"));
$build_index = array();
foreach ($build_index_list as $row) {
    list($src, $dst) = explode(":", $row);
    list($moduleFunctionName, $args) = explode(" ", $src, 2);
    $build_index[$moduleFunctionName] = array(trim($args), $dst);
}
unset($build_index_list);


$file = fopen($ssource, "r");
while (($line = fgets($file)) !== false) {
    $line = trim($line);
    
    if (preg_match("/^\#([A-z]+)\s+([A-z0-9]+)\s*(.*)$/", $line, $matches)) {
        list($all, $directive, $value, $args) = $matches;
        switch ($directive) {
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
		echo "#include \"$value.h\"\n";
                break;
	    default:
		//nothing
        }
    } else if (preg_match('/^([A-z0-9]+)([<>!@#][A-z0-9_]*)\s*([^\{]*)$/', $line, $matches)){
    //c< "Hello world"    - function call
	list($full, $module, $method, $arguments) = $matches;
	$realModule = $state['required'][$module][0];
	//echo $realModule.$method." ".$arguments."\n";
	if (isset($build_index[$realModule.$method])) { //это не расширение
	    $newline = "!" . $build_index[$realModule.$method][1] . "\n";
	    $args = explode(",", $arguments);
	    foreach ($args as $id => $value) {
		$newline = str_replace('ARG'.$id, $value, $newline);
	    }
	    echo $newline;
	}
    } else {
	echo $line."\n";
    }

    //c> fsm {            - function call with block start
    
    //tcp<tcp_host<"127.0.0.1"   - property set
    
}