<?php
function ting_openformat_admin_module_disable($form_state) {
  $form = array();
  $form['#submit'] = array('ting_openformat_admin_module_disable_form_submit');

  $form['ting_openformat']['TESTHEST'] = array(
    '#type' => 'textfield',
    '#title' => t('KROKODULLE'),
    '#default_value' => 'ZEBRA',
  );

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Disable this module'),
  );

  return $form;
}

function ting_openformat_admin_module_disable_form_submit($form, $form_state) {
//  dpm(func_get_args());
}
?>
