<?php

class CQLToCQLStrictParser {

  private $operators = array(
    '@ IKKE @' => ' not ',
    '@ NOT @' => ' not ',
    '@ ELLER @' => ' or ',
    '@ OR @' => ' or ',
    '@ OG @' => ' and ',
    '@ AND @' => ' and ',
  );

  public function parse($expression) {
    // Trim string
    $expression = str_replace('  ', ' ', $expression);

    $expression = $this->parseSubExpression($expression);

    $operators = array_keys($this->operators);
    $operator_replacements = array_values($this->operators);
    $expression = preg_replace($operators, $operator_replacements, $expression);

    return $expression;

  }

  private function parseSubExpression($expression) {


    // match all subexpressions recursively
    $sub_regex = '/(\((?>[^()]+|(?1))*\))/';
    preg_match_all($sub_regex, $expression, $match);

    if (!empty($match[1])) {
      foreach ($match[1] as $needle) {
        $nuddle = $this->trimString($needle);
        $replacement = $this->parseSubExpression($nuddle);
        $expression = str_replace($needle, '(' . $replacement .')', $expression);
      }
    }

    // Parse the rest
    $sub = preg_replace($sub_regex, '[SUB]', $expression);
    $expressions = explode('[SUB]', $sub);
    usort($expressions, 'self::sortStringsByLength');
    foreach ($expressions as $needle) {
      $replacement = $this->parseOperations($needle);
      $expression = str_replace($needle, $replacement, $expression);
    }

    return $expression;
  }

  private function getSearchCodes($expression) {
    $operators = array_keys($this->operators);
    $expressions_with_op = preg_replace($operators, '[OP]', $expression);
    $expressions = explode('[OP]', $expressions_with_op);
    usort($expressions, 'self::sortStringsByLength');
    return $expressions;
  }

  private function parseOperations($expression) {

    // Extract searchCode/value expressions
    $expressions = $this->getSearchCodes($expression);

    // Loop through expressions replace with strict cql
    foreach ($expressions as $needle) {
      $replacement = $this->parseSearchCode($needle);
      $expression = str_replace($needle, $replacement, $expression);
    }

    return $expression;

  }

  private function parseSearchCode($expression) {
    if (strpos($expression, '=') !== false) {
      list($searchcode, $searchvalue) = explode('=', $expression);
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

  private function sortStringsByLength($a, $b) {
    return strlen($b) - strlen($a);
  }

  private function trimString($expression, $first = '(', $last = ')') {
    if (substr($expression, 0, 1) === $first){
      $expression = substr($expression, 1);
    }
    if (substr($expression, -1, 1) === $last){
      $expression = substr($expression, 0, -1);
    }
    return $expression;
  }

}

