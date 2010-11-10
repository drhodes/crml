var nacllib = new NaclLib("nacl_module", "status", 1000);

// we use a custom detector for whether a module is ready or not
nacllib.numModulesReady = function(modules) {
  var count = 0;
  for (var i = 0; i < modules.length; i++) {
    try {
      var foo = modules[i].moduleReady();
      count += 1;
    } catch(e) {
      // do nothing
    }
  }
  return count;
};

// we use a custom detector for whether a module is ready or not
nacllib.areTherePluginProblems = function(modules) {
  return 0;
};

// The div where we report the events.
var event_box_2d = null;

// The javascript functions to add a line to the div.
var addLine2d = function(line) {
  event_box_2d.innerHTML = line + '<br>' + event_box_2d.innerHTML;
}

nacllib.test = function() {
  event_box_2d = document.getElementById("event_text_box_2d");;
  var plugin_obj_2d = document.getElementById("plugin_2d");
  // Add the banner to the top of the event log.
  addLine2d('<b>Event log</b>');
  // Set the plugin to report events to the event log.
  plugin_obj_2d.setTextBox(addLine2d);

  plugin_obj_2d.reportChecksum();
  if ('1' != plugin_obj_2d.isChecksumCheckSuccess()) {
    return "checksum check failed";
  }
  // Return success.
  return "";
};
