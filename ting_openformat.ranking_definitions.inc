<?php

/**
 * List of sort values used, by priority
 */

// use rank_subject if any of these search codes are used:
$ranking_definitions['rank_subject'][] = 'em';
$ranking_definitions['rank_subject'][] = 'lem';
$ranking_definitions['rank_subject'][] = 'term.subject';
$ranking_definitions['rank_subject'][] = 'term.genre';
$ranking_definitions['rank_subject'][] = 'dkcclterm.em';
$ranking_definitions['rank_subject'][] = 'dkcclphrase.lem';
$ranking_definitions['rank_subject'][] = 'phrase.subject';
$ranking_definitions['rank_subject'][] = 'phrase.genre';

// use rank_main_title if any of these search codes are used:
$ranking_definitions['rank_main_title'][] = 'ti';
$ranking_definitions['rank_main_title'][] = 'se';
$ranking_definitions['rank_main_title'][] = 'vp';
$ranking_definitions['rank_main_title'][] = 'term.title';
$ranking_definitions['rank_main_title'][] = 'term.maintitle';
$ranking_definitions['rank_main_title'][] = 'dkcclterm.ti';
$ranking_definitions['rank_main_title'][] = 'dkcclterm.vp';
$ranking_definitions['rank_main_title'][] = 'dkcclterm.se';
$ranking_definitions['rank_main_title'][] = 'dkcclphrase.lti';
$ranking_definitions['rank_main_title'][] = 'dkcclphrase.lvx';
$ranking_definitions['rank_main_title'][] = 'dkcclphrase.lse';
$ranking_definitions['rank_main_title'][] = 'dkcclphrase.lht';
$ranking_definitions['rank_main_title'][] = 'phrase.title';
$ranking_definitions['rank_main_title'][] = 'phrase.titleSeries';

// use rank_creator if any of these search codes are used:
$ranking_definitions['rank_creator'][] = 'fo';
$ranking_definitions['rank_creator'][] = 'po';
$ranking_definitions['rank_creator'][] = 'term.creator';
$ranking_definitions['rank_creator'][] = 'term.maincreator';
$ranking_definitions['rank_creator'][] = 'phrase.creator';

// if any other search codes are used:
$ranking_definitions['year_descending'] = array();

 // default sorting, if no search codes are used
$ranking_definitions['rank_frequency'] = array();
