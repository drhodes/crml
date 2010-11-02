// Class: Core
// desc: Manages the native client plugin booting process
//       used for

Core = function(plugin_name){
    this.plugin_ = plugin;
};

core.wire = function(subs) {
    var orderedSubs = ["gfx", "aud", "evt"];
    orderedSubs.foreach(function(s){
        if($.InArray(s, subs)){

        }
    });
};


Core.prototype.Alive = function(){
    this

}



core.wire(["gfx", "aud", "evt"]);


// get the core running
// is accepting commands?
// sort the subsystems by dependency

// is the evt system up and running?
// is the aud system up and running?
// is the gfx system up and running?

// ok. give all clear.
// start the user main loop


// this will fire a callback passed in
// by the user.  or .. not.
core.ready(core.mainloop());