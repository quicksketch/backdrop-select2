<?php
/**
 * @file
 * admin forms for select2.
 */

/**
 * Impelemnts hook_form().
 */
function select2_settings_form($form, &$form_state) {
  $config = config('select2.settings');

  $form['compression_type'] = array(
    '#type' => 'radios',
    '#title' => t('Choose Select2 compression level'),
    '#options' => array(
      'minified' => t('Production (Minified)'),
      'source' => t('Development (Uncompressed Code)'),
    ),
    '#default_value' => $config->get('compression_type'),
  );

  $form['use_for_all_select_elements'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use for all select elements'),
    '#description'   => t('If checked, Select2 plugin will be applied for all select elements on pages.'),
    '#default_value' => $config->get('use_for_all_select_elements'),
  );

  $form['use_for_all_select_elements_for_admin_pages'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use for all select elements on admin pages'),
    '#description'   => t('If checked, Select2 plugin will be applied for all select elements on admin pages.'),
    '#default_value' => $config->get('use_for_all_select_elements_for_admin_pages'),
    '#states' => array(
      'invisible' => array(
        ':input[name="select2_use_for_all_select_elements"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['use_for_autocomplete_elements'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use for select2 for elements with autocomplete'),
    '#description'   => t('If checked, Select2 plugin will be applied for all elements with autocomplete feature.'),
    '#default_value' => $config->get('use_for_autocomplete_elements'),
  );

  $form['default_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings'),
    '#collapsible' => 1,
    '#collapsed' => 1,
  );

  $form['default_settings']['min_options_count_for_search'] = array(
    '#type' => 'number',
    '#title' => t('Options count for enabling search.'),
    '#default_value' => $config->get('min_options_count_for_search'),
    '#min' => 0,
    '#max' => 9999,
    '#step' => 1,
    '#description' => t('If count of available options is less of value of this field, search box will be hided.'),
  );

  $form['excluded_elements'] = array(
    '#type' => 'fieldset',
    '#title' => t('Excluded elements'),
    '#collapsible' => 1,
    '#collapsed' => 1,
    '#description' => t('Lists of items that do not need to use the Select2 plugin.'),
  );

  $form['excluded_elements']['excluded_ids'] = array(
    '#type'          => 'textarea',
    '#title'         => t('IDs'),
    '#default_value' => $config->get('excluded_ids'),
    '#description'   => t('Enter one ID per line.'),
  );

  $form['excluded_elements']['excluded_cleasses'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Classes'),
    '#default_value' => $config->get('excluded_cleasses'),
    '#description'   => t('Enter one class per line.'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function select2_settings_form_submit($form, &$form_state) {
  $config = config('select2.settings');
  $values = $form_state['values'];
  $config->set('compression_type', $values['compression_type']);
  $config->set('use_for_all_select_elements', (bool) $values['use_for_all_select_elements']);
  $config->set('use_for_all_select_elements_for_admin_pages', (bool) $values['use_for_all_select_elements_for_admin_pages']);
  $config->set('use_for_autocomplete_elements', (bool) $values['use_for_autocomplete_elements']);
  $config->set('excluded_ids', $values['excluded_ids']);
  $config->set('excluded_classes', $values['excluded_classes']);
  $config->set('min_options_count_for_search', (int) $values['min_options_count_for_search']);
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}
