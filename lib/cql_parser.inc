<?php

function parse_expression($expression) {
  if (strpos($expression, '=') !== false) {
    $expressions = explode('=', $expression);
    $searchcode = $expressions[0];
    $searchvalue = $expressions[1];
    debug($expression);
    if (substr($searchvalue, 0) == '(' && substr($searchvalue, -1) == ')'){
      $searchvalue = parse_suboperation($searchvalue);
    }
    else if(!empty($searchvalue)) {
      $searchvalue = "'$searchvalue'";
    }

    $expression = $searchcode . "=" . $searchvalue;
  }
  else if(strpos($expression, ' ') !== false){
    $expression = "'$expression'";
  }

  return $expression;
}

function parse_operation($expression) {
  $operations = array(
    '@ IKKE @',
    '@ ELLER @',
    '@ OG @',
    '@ NOT @',
    '@ OR @',
    '@ AND @',
  );

  $operator_replacements = array(
    ' not ',
    ' or ',
    ' and ',
    ' not ',
    ' or ',
    ' and ',
  );

  $op = preg_replace($operations, '[OP]', $expression);

    $expressions = explode('[OP]', $op);
    foreach($expressions as $needle) {
      $replacement = parse_expression($needle);
      $expression = str_replace($needle, $replacement, $expression);
    }
    $expression = preg_replace($operations, $operator_replacements, $expression);

  return $expression;
}

function parse_suboperation($expression) {
  $sub_regex = '/\(([^\)]*)\)/';
  $sub = preg_replace($sub_regex, '[SUB]', $expression);

  preg_match_all($sub_regex, $expression, $match);

  if (!empty($match[1])){
    foreach($match[1] as $needle) {
      $replacement = parse_suboperation($needle);
      $expression = str_replace($needle, $replacement, $expression);
    }
  }

  $expressions = explode('[SUB]', $sub);
  foreach($expressions as $needle) {
    $replacement = parse_operation($needle);
    $expression = str_replace($needle, $replacement, $expression);
  }

  return $expression;
}
