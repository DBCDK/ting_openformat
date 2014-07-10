<?php

function parse_expression($expression) {

  if (strpos($expression, '=') !== false) {
    $expressions = explode('=', $expression);
    list($searchcode, $searchvalue) = $expressions;
    if (!empty($searchvalue)) {
      $searchvalue = "'$searchvalue'";
    }
    $expression = $searchcode . "=" . $searchvalue;
  }
  else if (strpos($expression, ' ') !== false) {
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
  usort($expressions, 'sort_expressions_by_length');
  foreach ($expressions as $needle) {
    $replacement = parse_expression($needle);
    $expression = str_replace($needle, $replacement, $expression);
  }
  $expression = preg_replace($operations, $operator_replacements, $expression);
  return $expression;
}

function parse_suboperation($expression) {
  $expression = str_replace('  ', ' ', $expression);

  $sub_regex = '/(\((?>[^()]+|(?1))*\))/';
  $sub = preg_replace($sub_regex, '[SUB]', $expression);

  preg_match_all($sub_regex, $expression, $match);
  debug($match[1]);

  if (!empty($match[1])) {
    foreach ($match[1] as $needle) {
      $nuddle = trim_expression($needle);
      debug($needle);
      $replacement = parse_suboperation($nuddle);
      $expression = str_replace($needle, '(' . $replacement .')', $expression);
    }
  }

  $expressions = explode('[SUB]', $sub);
  usort($expressions, 'sort_expressions_by_length');
  foreach ($expressions as $needle) {
    $replacement = parse_operation($needle);
    $expression = str_replace($needle, $replacement, $expression);
  }
  return $expression;
}

function trim_expression($expression) {
  if (substr($expression, 0, 1) === '('){
    $expression = substr($expression, 1);
  }
  if (substr($expression, -1, 1) === ')'){
    $expression = substr($expression, 0, -1);
  }
  return $expression;
}

function sort_expressions_by_length($a, $b) {
  return strlen($b) - strlen($a);
}

