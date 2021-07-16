/* A simple set of javascript objects designed to simplify the process of
 * converting between different coordinate systems in both 2D and 3D.
 *
 * Coordinate convention: In relation to your monitor: X points straight
 * out towards you, Z points towards the top of the screen, and Y points
 * towards the right of the screen.
 * 
 * Author: Matthew Bock
 * Updated: 2013.6.25
 */

//===================================================================
function rectangular2D(x, y)
{
	this.X = x;
	this.Y = y;

	this.toPolar = function()
	{
		var r = Math.sqrt((this.X * this.X) + (this.Y * this.Y));
		var t = Math.atan2(this.Y, this.X);

		var p = new polar(r, t);
		return p;
	}
}

//===================================================================
function polar(r, t)
{
	this.radius = r;
	this.azimuth = t;

	this.toRect = function()
	{
		var x = this.radius * Math.cos(this.azimuth);
		var y = this.radius * Math.sin(this.azimuth);

		var r = new rectangular2D(x, y);
		return r;
	}
}

//===================================================================
function rectangular3D(xcoord, ycoord, zcoord)
{
	this.X = xcoord;
	this.Y = ycoord;
	this.Z = zcoord;
	
	this.toCylinder = function()
	{
		var r = Math.sqrt((this.X) * (this.X) + (this.Y) * (this.Y));
		var a = Math.atan2(this.Y, this.X);

		var c = new cylindrical(r, a, this.Z);
		return c;
	}

	this.toSphere = function()
	{
		var rad = Math.sqrt(((this.X) * (this.X)) + ((this.Y) * (this.Y)) + ((this.Z) * (this.Z)));
		var incl = Math.acos((this.Z) / rad);
		var azim = Math.atan2(this.Y, this.X);

		var s = new spherical(rad, azim, incl);
		return s;
	};
}

//===================================================================
function cylindrical(r, a, zcoord)
{
	this.radius = r;
	this.azimuth = a;
	this.Z = zcoord;

	this.toRect = function()
	{
		var x = ((this.radius) * Math.cos(this.azimuth));
		var y = ((this.radius) * Math.sin(this.azimuth));

		var rect = new rectangular3D(x, y, this.Z);
		return rect;
	}

	this.toSphere = function()
	{
		var r = Math.sqrt((this.radius) * (this.radius) + (this.Z) * (this.Z));
		var i = Math.acos((this.Z) / (this.radius));

		var s = new spherical(r, this.azimuth, i);
		return s;
	}
}


//===================================================================
function spherical(r, a, i)
{
	this.radius = r;
	this.inclination = i;
	this.azimuth = a;
	
	this.elevation = (1.57 - this.inclination);
	this.latitude = ((this.elevation /Math.PI) * 180); // simplified version of (x / pi) * 180
	this.longitude = ((this.azimuth / Math.PI) * 180);

	this.toRect = function()
	{
		var x = (this.radius * Math.sin(this.inclination) * Math.cos(this.azimuth));
		var y = (this.radius * Math.sin(this.inclination) * Math.sin(this.azimuth));
		var z = (this.radius * Math.cos(this.inclination));

		var rect = new rectangular3D(x, y, z);
		return rect;
	};

	this.toCylinder = function()
	{
		var r = (this.radius * Math.sin(this.inclination));
		var z = (this.radius * Math.cos(this.inclination));

		var c = new cylindrical(r, this.azimuth, z);
		return c;
	};
	
}