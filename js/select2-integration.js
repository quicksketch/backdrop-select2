/**
 * @file
 * Select2 integration.
 */
(function ($) {
  "use strict";

  Backdrop.select2 = {};

  Backdrop.select2.autocompleteFormatResult = function (result) {
    console.log(result);
    return result.text;
  };

  Backdrop.select2.autocompleteFormatSelection = function (result) {
    return result.text;
  };

  Backdrop.select2.autocompleteInitSelection = function (element, callback) {
    console.log(element);
    console.log(callback);
    var def_values = $(element).select2('val');

    callback({
      id: def_values,
      text: def_values
    });

  };

  Backdrop.select2.autocompleteAjax = function ($element) {
    var url = $element.data('use-select2-autocomplete');
    return {
      url: function(value) {
        return url + '/' + value.term;
      },
      dataType: 'json',
      cache: true,
      processResults: function (data) {
        // Note we return the value of more so Select2 knows if more results can
        // be loaded.
        var results_out = [];

        $.each(data, function (id, title) {
          results_out.push({
            id: id,
            text: title
          });
        });

        return {
          results: results_out
        };
      },
      params: {
        error: function (jqXHR, textStatus, errorThrown) {
          if (textStatus == 'abort') {}
        }
      }
    };
  };
  Backdrop.behaviors.select2 = {
    attach: function (context) {
      var $context = $(context);
      $context.find('input[data-use-select2-autocomplete]').each(function() {
        var $element = $(this);
        $element.select2({
          ajax: Backdrop.select2.autocompleteAjax($element)
        });
      });
      $context.find('select[data-use-select2]').select2();
    }
  };

})(jQuery);
