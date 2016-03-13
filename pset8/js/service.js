/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 */


// Shuttle's default values
// ========================

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 100;

// max search range for autoplot
var RANGE_MAX = 10000;

// Global References
// =================

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;
  
// number of available seats
var seatCtr = SEATS;

// dropCtr
var dropCtr = 0;

        
// load APIs
// =========
       
// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});


// Ready to respond to user's input
// ================================

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        // reset announcement
        $("#announcements").html("no announcements at this time");
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });


    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});


// ***********************
//      functions    
// ***********************

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 15,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}


/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();
    

    // populate Earth with passengers and houses
    populate();
}


/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}


/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}


/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}


/**
 * Renders seating chart.
 */

function chart()
{
    var html = "<div id=\"tableFrame\"><table>";
    
    for (var i = 0; i < SEATS; i++)  // iterate over seats
    {
        if (shuttle.seats[i] == null)    // seat is empty
        {
            if (i % 2)  // odd numbers
            { 
                html += "<td>Empty</td>";
                html += "</tr>";
            }
            else        // even numbers
            { 
                html += "<tr>";
                html += "<td>Empty</td>";
            }
        }
        else    
        { 
            if (i % 2)  // odd numbers
            { 
                html += "<td id ='seat'>" + shuttle.seats[i]["name"] + "</td>";
                html += "</tr>";
            }
            else        // even numbers
            { 
                html += "<tr>";
                html += "<td id ='seat'>" + shuttle.seats[i]["name"] + "</td>";
            }
        }
    }
    html += "</table></div>";
    
    $("#chart").html(html);
}


/**
 * Populates Earth with passengers and houses.
 */
function populate()
{    
    // mark houses
    for (var house in HOUSES)  // Iterates over the enumerable properties of an object, in arbitrary order. 
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        
        // Placemark (3D Earth)
        // ====================   
        
            // https://developers.google.com/earth/documentation/placemarks
        
        // Create the placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);  // message to show next to placemark icon

        // Define a custom icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");  // href to staff pics

        // prepare icon's style
        var style = earth.createStyle("");     // create a new style
        style.getIconStyle().setIcon(icon);    // apply the icon to the style
        style.getIconStyle().setScale(4.0);    // a scale of 1.0 corresponds to 100%.

        // prepare stylemap
        // to provide separate normal and highlighted styles for a placemark
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);     
        styleMap.setHighlightStyle(style);  // highlighted version appears when user mouses over the icon

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point (passenger's location)
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);


        // marker (2D Map)
        // ===============
        
            // https://developers.google.com/maps/documentation/javascript/markers
        
        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });


        // remember passenger's location(placemark and marker)
        PASSENGERS[i].lat = building.lat;    // add to PASSENGERS array
        PASSENGERS[i].lng = building.lng; 
        PASSENGERS[i].marker = marker;
        PASSENGERS[i].placemark = placemark;
    }
}


/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    return true;
}


/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}


/**
 * Picks up nearby passengers.
 */
 
function pickup()
{
    // Seach for a near passenger within passed range
    // ===============================================
    var near = null;
    near = lookforPassenger(15.0);  // return passenger, if not found null
    
    // No one is within the range
    if (near === null)
    {
        $("#announcements").html("Outside of pick-up service range (15.0 meters)");
        return false;
    }     
    
    // check availability of seats
    // ===========================
    
    // to remember an available seat index
    var available = null;
    
    // check availability of seats
    if (0 < seatCtr && seatCtr <= SEATS)    
    {
        // look for open seat
        for (var i = 0; i < SEATS; i++)
        {
            if (shuttle.seats[i] == null)
            {             
                // remember seat's index
                available = i;
            }
        }
    }
    else
    {
        // within the range but no seats are free
        $("#announcements").html("Sorry! Shutte is full");
        return 1;
    }
    

    // give near passenger a seat
    // ==========================       
    
    if (near !== null)
    {                                    
        // give a seat to passenger
        shuttle.seats[available] = near;

        $("#announcements").html("Hello, " + near.name + "!");
                                
        // update chart
        chart();
                                            
        // update number of available seats
        seatCtr = seatCtr - 1;
                            
                            
        // remove marker and placemark
        // ===========================
                                                      
        // remove passenger from 2D map
        near.marker.setMap(null);
        near.marker = null;
                                                    
        // remove passenger from 3D earth
        var features = earth.getFeatures();
        features.removeChild(near.placemark);
        near.placemark = null;
    }
}  


/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    // ensure that passenger exists onboard
    if (seatCtr === SEATS)
    {
        $("#announcements").html("No one is onboard");
        return false;
    }
    
    var closest = getDestination(30.0);
    
    if (closest === false)
    {
        $("#announcements").html("Outside of drop-off service range (30.0 meters)");
        return false;
    }
    
    // drop off
    for (var k = 0; k < shuttle.seats.length; k++)
    {
        if (shuttle.seats[k] != null)
        {
            if (shuttle.seats[k].house == closest.house)
            {
                $("#announcements").html("Good-bye, " + shuttle.seats[k].name + "!");
                
                shuttle.seats[k] = null;
                seatCtr = seatCtr + 1;
                dropCtr = dropCtr + 1;
                
                // update chart
                chart();
                
                return 0;
            }
        }
    }
}


/**
 * Announce the address of current location
 *
 * inform passengers, as via an announcement, of the shuttle’s current location.
 * http://code.google.com/apis/maps/documentation/geocoding/#ReverseGeocoding
 */
 
function currentLocation()
{
    // get current latitude/longitude value
    var latlng = [shuttle.position.latitude, shuttle.position.longitude];   
    latlng = latlng.toString();
 
    // prepare url
    url = "https://maps.googleapis.com/maps/api/geocode/json?latlng=" + latlng;
    
    // request address data set(in JSON)
    $.getJSON(url, function(data){
        
        //extract only formatted address
        var address = data.results[0].formatted_address;
        
        // show address in announcement
        $("#announcements").html(address);
    }); 
}


/**
 * automatically pick up and drop off passengers by teleporting
 */
 
function autopilot()
{                 
    if (seatCtr > 0)
    {  
        // autoPickup
        // ==========
               
        var time_id1 = setInterval( function(){
            
            // to ensure successful pickup
            var ctrBefore = seatCtr;
            
            // call autoPickup
            autoPickup();
            
            if (seatCtr === 0 || seatCtr === ctrBefore)
            {  
                clearInterval(time_id1);
                
                // autoDropoff
                // ===========
                var time_id2 = setInterval( function(){
                    
                    // to ensure successful dropoff
                    var ctrBefore = seatCtr;
                    
                    // call autoDropoff
                    autoDropoff();
                    if (seatCtr === 10 || seatCtr === ctrBefore)
                    {  
                        console.log("dropCtr: "+dropCtr);
                        clearInterval(time_id2);
                    }    
                }, 1000 );    
                
            }
        }, 1000 ); 
    }    
    // only autoDropoff if seats are full
    // =============================
    else if (seatCtr === 0)
    {
        var time_id2 = setInterval( function(){
            
            // to ensure successful dropoff
            var ctrBefore = seatCtr;
            
            // call autoDropoff
            autoDropoff();
            if (seatCtr === 10 || seatCtr === ctrBefore)
            {  
                console.log("dropCtr: "+dropCtr);
                clearInterval(time_id2);
            }    
        }, 1000 );    
    }
}


/**
 * Seach for closest passenger within passed range
 * return passenger, if not found false
 */
function lookforPassenger(range_max)
{    
    // initial search range
    var range = 15;
        
    while (range <= range_max)
    {
        console.log('range' + range);
        
        for (var i = 0; i < PASSENGERS.length; i++)
        {
            if (PASSENGERS[i]["marker"] !== null)  //exclude those already onboard
            {
                // calculate distance from each passenger (in meters)
                var d = shuttle.distance(PASSENGERS[i].lat, PASSENGERS[i].lng);
                    
                // if within the range
                if (d <= range)   
                {
                    var isOK = validatePassenger(PASSENGERS[i])
                    
                    if (isOK)
                    {
                        return PASSENGERS[i];
                    }
                }
            }
        }
        // widen the search range
        range *= 2;   
    }
    return null;
}


/**
 * if no one to pick up return null
 * if seat is full true
 */
 
function autoPickup(){

    console.log('***** autoPickup started *****');
    
    // Seach for closest passenger within passed range
    // ===============================================
    var near = null;
    near = lookforPassenger(RANGE_MAX);    // return passenger odject, else null
              
    if (near == null)
    {
        $("#announcements").html("Could not find any passenger");
        console.log('***** autoPickup ended (no passenger found) *****');
        
        return null;
    }
    
    console.log('near: '+near.name);
                                      
    // check availability of seats
    // ===========================
    if (seatCtr == 0)
    {
         $("#announcements").html("No seat is free");
         console.log('***** autoPickup ended (seats full) *****');
         
         return false;
    } 
               
    // storage
    var available = null;
                
    // check availability of seats
    if (0 < seatCtr && seatCtr <= SEATS)    
    {
        // look for open seat
        for (var i = 0; i < SEATS; i++)
        {
            if (shuttle.seats[i] == null)
            {             
                // remember seat's index
                available = i;
            }
        }
    }

    // give a seat to passenger
    // ========================
    
    shuttle.seats[available] = near;
    $("#announcements").html("Hello, " + near.name + "!");
                                    
    // update chart
    chart();
                                                
    // update number of available seats
    seatCtr = seatCtr - 1;                                
                                
    // remove marker and placemark
    // ===========================
                                                          
    // remove passenger from 2D map
    near.marker.setMap(null);
    near.marker = null;
                                                        
    // remove passenger from 3D earth
    var features = earth.getFeatures();
    features.removeChild(near.placemark);
    near.placemark = null;
        
    // move shuttle            
    teleport(near.lat, near.lng);  
    
    console.log('seatCtr: '+seatCtr);
    console.log('***** autoPickup ended *****');
    return;
}
    
    
/**
 * teleport to the passed point on map
 */

function teleport(lat, lng)
{
    // change shuttle's position
    shuttle.position.latitude = lat;
    shuttle.position.longitude = lng;
        
    // update map
    viewchange();
}


/**
 * return the closest destination house within passed range
 * object{distance: int, house: str}, else false
 */

function getDestination(range_max)
{
    // search for destinations
    // =======================
    
    // storage
    var destinations = new Array();

    // iterate over all passengers onboard
    for (var i = 0; i < SEATS; i++)
    {
        if (shuttle.seats[i] != null)
        {
            // remember all the destinations (house names)
            if (shuttle.seats[i]["house"] != undefined)
            {
                destinations.push(shuttle.seats[i]["house"]);  
            }
        }
    }
    if (destinations.length === 0)
    {
        console.log('No destination found');
        return null;
    }
    
    if (destinations.length > 1)
    {       
        // remove duplicates
        destinations = destinations.filter( function(item, index, inputArray) {
               return inputArray.indexOf(item) == index;
        });
    }

    
    // check distance to each destination
    // ==================================
    
    // storage
    var distances = new Array();
    
    for (var j = 0; j < destinations.length; j++)
    {
        // get each house name (as key) from HOUSES 
        $.each(HOUSES, function(key){    
            if (destinations[j] == key)    // destination matches key
            {
                // calculate distance to each destination (in meters)
                var d = shuttle.distance(HOUSES[key].lat, HOUSES[key].lng);
               
                // if within the range
                if (d <= range_max)
                { 
                    // remember each distance value with house name as a key
                    distances.push({distance: d, house: key, lat: HOUSES[key].lat, lng: HOUSES[key].lng}); 
                }
            }
        });
    }
    
    // No destination is within the range
    if (distances.length == 0)
    {
        return false;
    }
    
    // find out the closest destination
    // ================================
    
    if (destinations.length > 1)
    {
        // sort in descending order
        var distances = distances.sort(function(a,b) {
            return b.distance - a.distance;
        }); 
    }
    
    // closest point
    var closest = distances.pop();
    
    return closest;
}


/**
 * return number of open seats
 */

function autoDropoff()
{
    console.log('***** autoDropoff started *****');
    if (0 <= seatCtr && seatCtr < SEATS)
    {  
        // search for closest house
        var closest = null;
        closest = getDestination(RANGE_MAX);    // object{distance: int, house: str}, else false
        
        if (closest == null)
        {
            console.log('Closest house not found' );
            return false;
        }

        console.log('closest.house: ' + closest.house+'   ' + closest.distance);
        
        // drop off
        for (var i = 0; i < shuttle.seats.length; i++)
        {
            if (shuttle.seats[i] != null)
            {
                if (shuttle.seats[i].house == closest.house)
                {
                    $("#announcements").html("Good-bye, " + shuttle.seats[i].name + "!");
                    
                    shuttle.seats[i] = null;
                    seatCtr = seatCtr + 1;
                    dropCtr = dropCtr + 1;
                    
                    // update chart
                    chart();
                    break;
                }
            }
        }

        // move shuttle            
        teleport(closest.lat, closest.lng);           
    }
    
    console.log('seatCtr: '+seatCtr);
    console.log('***** autoDropoff ended *****');
    return seatCtr;
}

/**
 * ensure that passenger lives in one of the registered houses
 */

function validatePassenger(p)
{
    // ensure the passenger is registered for houses
    var ctr = 0;
    $.each( HOUSES, function( key ) {
        if (p.house === key)
        {
            ctr++;
        }
    } );
    
    if (ctr)
    {
        return true;
    }
    else
    {
        console.log('* ineligible passenger excluded *');
        return false;
    }
}


/**
 * group seated passengers' names by house
 */
 
function groupPassenger()
{
    if (seatCtr === 10)
    {
        $("#announcements").html("All seats are empty"); 
        return false;
    }
    
    var groups = new Array();
    
    // check each house
    $.each( HOUSES, function( key ) {
        
        var temp = new Array();
        
        for (var i = 0; i < SEATS; i++)  // iterate over seats
        {         
            if (shuttle.seats[i] !== null)
            {
                if (shuttle.seats[i].house === key)
                {
                    // remember residents as array
                    temp.push(shuttle.seats[i].name)
                }
            }                      
        }
        if (temp.length > 0)
        {
            // make JSON
            groups.push({ house : key , residents : temp });
        }
    });
    
    // write html
    // ==========
    
    // open list
    var html = "<div id=\"groupPassenger\">";  
    
    // for each group
    for (var j = 0; j < groups.length; j++)
    {      
        html += "<div id=\"eachGroup\"><h4 id=\"house\">" + groups[j].house + "</h4>";    // add header
        html += "<ul>"
        
        // for each resident
        for (var k = 0; k < groups[j].residents.length; k++)
        {            
            html += "<li id=\"resident\">" + groups[j].residents[k] + "</li>";    // add paragraph
        }
        html += "</ul></div>"
    }
    
    // close list
    html += "</div> ";  

    // replace chart
    $("#chart").html(html);
}
