<?php
function ting_openformat_admin_module_disable($form_state) {
  $form = array();
  $form['#submit'] = array('ting_openformat_admin_module_disable_form_submit');

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Disable this module'),
  );

  return $form;
}

function ting_openformat_admin_module_disable_form_submit($form, $form_state) {

  // @TODO
  // 1. delete fields attached to ting_openformat module
  // 2. disable modules that had any fields attached
//  dpm(func_get_args());
}
?>
