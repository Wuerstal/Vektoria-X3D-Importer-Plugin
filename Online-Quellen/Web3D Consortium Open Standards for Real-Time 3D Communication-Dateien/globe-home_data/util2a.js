
// a 


// Define control panel

CP = new Object();
CP.display = new Object();
CP.display.weather = 1;		// turn on weather info display



function resetView()
{
var scene = document.getElementById('scene');
var oldViewPoint = document.getElementById('mainView');
		
var newViewPoint = oldViewPoint.cloneNode(true);
		
scene.appendChild(newViewPoint);

newViewPoint.setAttribute('set_bind','true');
		
scene.removeChild(viewPoint);
}

function trunk3(num)
{
	return Math.round(num * 1000) / 1000;
}

function reportCoords(e)
{
	var x = e.hitPnt[0];
	var y = e.hitPnt[1];
	var z = e.hitPnt[2];

	// Axes are re-oriented into something that makes more sense for the Earth model/texture
	var rect = new rectangular3D(z, x, y);

	// Only truncate the numbers right before they're printed. Accuracy, and readability!
	//$('#cartCoords').text('X: ' + trunk3(rect.X) + ', Y: ' + trunk3(rect.Y) + ', Z: ' + trunk3(rect.Z));

	var sphere = rect.toSphere();
	
	//$('#sphereCoords').text('Radius: ' + trunk3(sphere.radius) + ', Elevation: ' + trunk3(sphere.elevation) + ', Azimuth: ' + trunk3(sphere.azimuth));
	//$('#latLongCoords').text('Latitude ' + trunk3(sphere.latitude) + ', by Longitude ' + trunk3(sphere.longitude));

	window.selectedLat = sphere.latitude;
	window.selectedLng = sphere.longitude;
	
	getWeatherData();
}


function getWeatherData()
{

	if (CP.display.weather) {

	$('#dataDump').text('Fetching...');

	var url = "http://api.openweathermap.org/data/2.5/weather?lat="
						+ window.selectedLat
						+"&lon=" + window.selectedLng
						+"&APPID=88fa7890a433ef8df051938595216b10"
						+"&callback=?";

	$.getJSON(url, null, function(data)
			{
				$('#dataDump').text("");

				$('#dataDump').append("<u><b>Closest Weather Data</b></u>");
				$('#dataDump').append("<br>");

				$('#dataDump').append("<b>City:</b> "+ data["name"] + ", "  + data["sys"]["country"]);
				$('#dataDump').append("<br>");

				$('#dataDump').append("<b>Location:</b> " + data["coord"]["lat"] + " Latitude by " + data["coord"]["lon"] + " Longitude.");
				$('#dataDump').append("<br>");

				$('#dataDump').append("<b>Right Now:</b> " + data["weather"][0]["description"]);
				$('#dataDump').append("<br>");

				var ftemp = Math.round(((parseInt(data["main"]["temp"]) - 273.15) * 1.8) + 32);
				$('#dataDump').append("<b>Temperature:</b> " + ftemp + "F");
				$('#dataDump').append("<br>");

				$('#dataDump').append("<b>Humidity: </b>" + data["main"]["humidity"] + "%");
				$('#dataDump').append("<br>");

				var speed = parseInt(data["wind"]["speed"]) * 2.237;
				$('#dataDump').append("<b>Wind:</b> " + speed + "mph at " + data["wind"]["deg"] + " degrees");
				$('#dataDump').append("<br>");

				$('#dataDump').append("<b>Cloud Coverage:</b> " + data["clouds"]["all"] + "%");
				$('#dataDump').append("<br><br>");

				$('#dataDump').append("Data courtesy of <a href='http://www.openweathermap.org'>openweathermap.org</a>");

			});
	}
}

function getStreetMapData() // NOT USED NOW
{
	var zoom = document.getElementById('zoomLevel');
	var type = document.getElementById('mapType');

	var url = "http://open.mapquestapi.com/staticmap/v4/"
				+ "getmap?size=600,400"
				+ "&zoom=" + zoom.options[zoom.selectedIndex].value
				+ "&center=" + window.selectedLat + "," + window.selectedLng
				+ "&type=" + type.options[type.selectedIndex].value;

	$('#dataDump').append("<img src='" + url +"' />");
	$('#dataDump').append("<br>Map data from <a href='http://open.mapquestapi.com/'>MapQuest's Open Data</a>");
}

function initLocation (){  // use browser geo location services?
	
	//window.selectedLat = ;
	//window.selectedLng = ;	
	//onclick timesensor kickoff... document.getElementById('Wizard').setAttribute('startTime',(new Date().getTime() / 1000).toString());
	
	getWeatherData(); // default return is fine
}


function fetchHandler()
{
	if (window.selectedLat == null && window.selectedLng == null)
	{
		alert("You must select a location.");
		return;
	};
	
		getWeatherData();
	
}

