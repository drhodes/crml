// -----------------------------------------------------------------------------
hello_world = null;  // Global application object.
status_text = 'NO-STATUS';

function moduleDidLoad() {
    hello_world = document.getElementById('plugin_2d');
    //fortytwo();
    updateStatus("asdf");
}

// If the page loads before the Native Client module loads, then set the
// status message indicating that the module is still loading.  Otherwise,
// do not change the status message.
function pageDidLoad() {
    if (hello_world == null) {
        updateStatus('LOADING...');
    } else {
        // It's possible that the Native Client module onload event fired
        // before the page's onload event.  In this case, the status message
        // will reflect 'SUCCESS', but won't be displayed.  This call will
        // display the current message.
        updateStatus();
    }
}

function partition(str){
    // take a string, bust it into blocks
    // return an array of blocks
    const block_size = 1024*64;  // 64 <= 99
    const len = str.length;
    var blocks = [];
    for (i=0; i<len; i+=block_size) {
        blocks.push(str.slice(i, i+block_size));
    }
    return blocks;
}

function fortytwo() {
    loadStatus("> Loading file");
    $.get('example.hex', function(data) {
        const blocks = partition(data);
        hello_world.store_hex("example", blocks[0]);
        for (i=1; i<blocks.length; i++){
            addLine2d(""+i);
            hello_world.append_hex("example",  blocks[i]);
        }
    });
    loadStatus("> Loading done.");
}

function store_hex() {
    try {
        hello_world.store_hex("example", _example_hex[0]);
        for (i=1; i<_example_hex.length; i++){
            hello_world.append_hex("example",  _example_hex[i]);
        }
    } catch(e) {
        alert(e.message);
    }
}


function helloworld() {
    try {
        alert(hello_world.helloworld());
    } catch(e) {
        alert(e.message);
    }
}

// Set the global status message.  If the element with id 'status_field'
// exists, then set its HTML to the status message as well.
// opt_message The message test.  If this is null or undefined, then
//     attempt to set the element with id 'status_field' to the value of
//     |status_text|.
function updateStatus(opt_message) {
    if (opt_message)
        status_text = opt_message;
    var status_field = document.getElementById('status_field');
    if (status_field) {
        status_field.innerHTML = status_text;
    }
}

function loadStatus(opt_message) {
    if (opt_message)
        status_text = opt_message;
    var status_field = document.getElementById('load-status');
    if (status_field) {
        status_field.innerHTML = status_text;
    }
}


//-----------------------------------------------------------------------------




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
    //hook up the hello world example.
    moduleDidLoad();
    pageDidLoad();

    // end of hello world.

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


