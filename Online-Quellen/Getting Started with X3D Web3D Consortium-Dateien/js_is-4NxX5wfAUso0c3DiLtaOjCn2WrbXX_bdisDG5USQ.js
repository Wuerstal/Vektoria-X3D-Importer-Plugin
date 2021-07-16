/*
 * Custom JS code.
 *	Most of this is to handle the spec comment form
 *	Defined variables manage the flow of the allowed drop-down when choosing a spec
 *	Structure:
 *		Form descriptor is a hash with the following fields
 *			name	The displayed name in the drop-down
 *			value	The value when selecting that item
 *			selected	Indicates if this value is selected by default
 *			part/version	A contain for the next level down
 *
 *		verN*	Hash of hash. Each entry contains a version description. '*' is "Only" or "Choices" 
 *				indicating the range of version items. 'N' is the major version #
 *		totalSpecificationChoices
 *				Master hash of hashes that covers the 3 specification drop-downs
 *		formIds	A hash of the HTML 'id' values corresponding to the three 'select' elements
 *		formElements
 *				A hash containing a reference to the elements whose 'id' values are stored in formIds.
 *				This is populated on page load complete (jQuery ready)
*/
var ver4Only = {
			"V4_0"	: {
					"name"		: "V4.0",
					"value"		: "V4_0",
					"selected"	: true
					}
	};
var ver4Choices = {
			"V4_0"	: {
					"name"		: "V4.0",
					"value"		: "V4_0",
					"selected"	: true
					},
			"V3_3"	: {
					"name"		: "V3.3",
					"value"		: "V3_3",
					"selected"	: false
					},
			"V3_2"	: {
					"name"		: "V3.2",
					"value"		: "V3_2",
					"selected"	: false
					},
			"V3_1"	: {
					"name"		: "V3.1",
					"value"		: "V3_1",
					"selected"	: false
				},
			"V3_0"	: {
					"name"		: "V3.1",
					"value"		: "V3_1",
					"selected"	: false
				}
	};
var ver3Choices = {
			"V3_3"	: {
					"name"		: "V3.3",
					"value"		: "V3_3",
					"selected"	: true				},
			"V3_2"	: {
					"name"		: "V3.2",
					"value"		: "V3_2",
					"selected"	: false
				},
			"V3_1"	: {
					"name"		: "V3.1",
					"value"		: "V3_1",
					"selected"	: false
				},
			"V3_0"	: {
					"name"		: "V3.0",
					"value"		: "V3_0",
					"selected"	: false
				}
	};
var ver2Only = {
			"V2_0"	: {
					"name"		: "V2.0",
					"value"		: "V2_0",
					"selected"	: true
				}
	};
var ver1Only = {
			"V1_0"	: {
					"name"		: "V1.0",
					"value"		: "V1_0",
					"selected"	: true				}
	};
var totalSpecificationCount = 6;	
var totalSpecificationChoices = [
			{
				"name"	: " Select -",
				"value"	: "",
				"selected"	: false,
				"part" : {}
			},
			{
				"name"		: "19775-x: X3D Architecture",
				"value"		: "19775",
				"selected"	: true,
				"part"		: {
						"19775_1" : {
							"name"		: "19775-1: Abstract X3D Definitions",
							"value"		: "19775_1",
							"selected"	: true,
							"version"	: ver4Choices
							},
						"19775_2" : {
							"name"		: "19775-2: Abstract SAI",
							"value"		: "19775_2",
							"selected"	: false,
							"version"	: ver3Choices
							}
				}
			},
			{
				"name"	: "19776-x: X3D Language Encodings",
				"value"	: "19776",
				"selected"	: false,
				"part" : {
						"19776_1" : {
							"name"		: "19776-1: XML Encoding",
							"value"		: "19776_1",
							"selected"	: true,
							"version"	: ver3Choices
							},
						"19776_2" : {
							"name"		: "19776-2: ClassicVRML Encoding",
							"value"		: "19776_2",
							"selected"	: false,
							"version"	: ver3Choices
							},
						"19776_3" : {
							"name"		: "19776-3: Compressed Binary Encoding",
							"value"		: "19776_3",
							"selected"	: false,
							"version"	: {
									"V3_3"	: {
										"name"		: "V3.3",
										"value"		: "V3_3",
										"selected"	: true
									},
									"V3_2"	: {
										"name"		: "V3.2",
										"value"		: "V3_2",
										"selected"	: false
									},
									"V3_1"	: {
										"name"		: "V3.1",
										"value"		: "V3_1",
										"selected"	: false
									}
								}
							},
						"19776_4" : {
							"name"		: "19776-4: Efficient Binary Encoding",
							"value"		: "19776_4",
							"selected"	: false,
							"version"	: ver4Only
							},
						"19776_5" : {
							"name"		: "19776-5: JSON Encoding",
							"value"		: "19776_5",
							"selected"	: false,
							"version"	: ver4Only
							}
				}
			},
			{
				"name"	: "19777-x: X3D Language Bindings",
				"value"	: "19777",
				"selected"	: false,
				"part" : {
						"19777_1" : {
							"name"		: "19777-1: ECMAScript Language Binding",
							"value"		: "19777_1",
							"selected"	: true,
							"version"	: {
									"V3_3"	: {
										"name"		: "V3.3",
										"value"		: "V3_3",
										"selected"	: true
									},
									"V3_0"	: {
										"name"		: "V3.1",
										"value"		: "V3_1",
										"selected"	: false
									}
								}
						},
						"19777_2" : {
							"name"		: "19777-2: Java Language Binding",
							"value"		: "19777_2",
							"selected"	: false,
							"version"	: {
									"V3_0"	: {
										"name"		: "V3.1",
										"value"		: "V3_1",
										"selected"	: true									}
									}
						},
						"19777_3" : {
							"name"		: "19777-3: C Language Binding",
							"value"		: "19777_3",
							"selected"	: false,
							"version"	: ver4Only
						},
						"19777_4" : {
							"name"		: "19777-4: C++ Language Binding",
							"value"		: "19777_4",
							"selected"	: false,
							"version"	: ver4Only
						},
						"19777_5" : {
							"name"		: "19777-5: C# Language Binding",
							"value"		: "19777_5",
							"selected"	: false,
							"version"	: ver4Only
						},
						"19777_6" : {
							"name"		: "19777-6: Python Language Binding",
							"value"		: "19777_6",
							"selected"	: false,
							"version"	: ver4Only
						}
				}
			},
			{
				"name"	: "19774-x: HAnim",
				"value"	: "19774",
				"selected"	: false,
				"part" : {
						"19774_1" : {
							"name"		: "19774-1: HAnim Architecture",
							"value"		: "19774_1",
							"selected"	: true,
							"version"	: ver2Only
							},
						"19774_2" : {
							"name"		: "19774-2: 19774-1: HAnim Motion Capture",
							"value"		: "19774_2",
							"selected"	: false,
							"version"	: ver2Only
							},
						"19774" : {
							"name"		: "19774: HAnim",
							"value"		: "19774",
							"selected"	: false,
							"version"	: ver1Only
							}
				}
			},
			{
				"name"	: "14772: VRML",
				"value"	: "14772",
				"selected"	: false,
				"part" : {
						"14772" : {
							"name"		: "14772: Virtual Reality Modeling Language",
							"value"		: "14772",
							"selected"	: false,
							"version"	: ver2Only
							},
						"14772A1" : {
							"name"		: "14772: VRML Amendment 1",
							"value"		: "14772A1",
							"selected"	: true,
							"version"	: {
									"V2_1"	: {
										"name"		: "V2.1",
										"value"		: "V2_1",
										"selected"	: true									}
								}
							}
				}
			}
	];
totalSpecificationChoices[19775] = totalSpecificationChoices[1];
totalSpecificationChoices[19776] = totalSpecificationChoices[2];
totalSpecificationChoices[19777] = totalSpecificationChoices[3];
totalSpecificationChoices[19774] = totalSpecificationChoices[4];
totalSpecificationChoices[14772] = totalSpecificationChoices[5];
var formIds = {
		"Specification"	: "edit-submitted-specification-document-set-specification-type",
		"Part"			: "edit-submitted-specification-document-set-specification-document",
		"Version"		: "edit-submitted-specification-document-set-version"
	};


jQuery(document).ready(function($) {

var formElements = {
		"Specification"	: document.getElementById (formIds.Specification),
		"Part"			: document.getElementById (formIds.Part),
		"Version"		: document.getElementById (formIds.Version)
	};
	
	updateSpecification();

// Event handlers for changes to drop-downs
	$('#'+formIds.Specification).change (function(ev) {
		var ndx = ev.target.selectedIndex;
		var value = ev.target.options[ndx].value;
		if (value == '') {value = 0;}
		var entry = totalSpecificationChoices[value];
		updatePart (entry)
	});
	$('#'+formIds.Part).change (function(ev) {
		var ndx = formElements.Specification.selectedIndex;
		var value = formElements.Specification.options[ndx].value
		var entry = totalSpecificationChoices[value];

		ndx = ev.target.selectedIndex;
		value = ev.target.options[ndx].value;
		var part = entry.part[value]
		updateVersion (part)
	});

// Routines to maintain correct consistency of drop-downs
	function updateSpecification() {
		formElements['Specification'].options.length = 0;
		formElements['Part'].options.length = 0;
		formElements['Version'].options.length = 0;
		for (ii=0; ii<totalSpecificationCount; ii++) {
			formElements.Specification.options[formElements['Specification'].options.length] = new Option (totalSpecificationChoices[ii].name, totalSpecificationChoices[ii].value, totalSpecificationChoices[ii].selected, totalSpecificationChoices[ii].selected);
			if (totalSpecificationChoices[ii].selected) {
				updatePart (totalSpecificationChoices[ii]);
			}
		}
	}
	function updatePart (entry) {
		formElements['Part'].options.length = 0;
		formElements['Version'].options.length = 0;
		for (sPart in entry.part) {
			formElements.Part.options[formElements['Part'].options.length] = new Option (entry.part[sPart].name, entry.part[sPart].value, entry.part[sPart].selected, entry.part[sPart].selected);
			if (entry.part[sPart].selected) {
				updateVersion (entry.part[sPart]);
			}
		}
	}
	function updateVersion (items) {
		formElements['Version'].options.length = 0;
		for (item in items.version) {
			formElements.Version.options[formElements['Version'].options.length] = new Option (items.version[item].name, items.version[item].value, items.version[item].selected, items.version[item].selected);
		}
	}


  $('.nav-toggle').click(function() {
    $('#main-menu div ul:first-child').slideToggle(250);
    return false;
  });
  if( ($(window).width() > 640) || ($(document).width() > 640) ) {
      $('#main-menu li').mouseenter(function() {
        $(this).children('ul').css('display', 'none').stop(true, true).slideToggle(250).css('display', 'block').children('ul').css('display', 'none');
      });
      $('#main-menu li').mouseleave(function() {
        $(this).children('ul').stop(true, true).fadeOut(250).css('display', 'block');
      })
        } else {
    $('#main-menu li').each(function() {
      if($(this).children('ul').length)
        $(this).append('<span class="drop-down-toggle"><span class="drop-down-arrow"></span></span>');
    });
    $('.drop-down-toggle').click(function() {
      $(this).parent().children('ul').slideToggle(250);
    });
  }
  
  // --> Handle block elements with 'link' class as simple anchors if it has the 'data-href' attribute
	$('.link').click(function(e) {
		uri = $(this).attr('data-href');
		if (uri != '') {
			window.open(uri, '_blank');
		}
	});
 
// Script to populate specification comment form drop-down
/*
	$('#edit-submitted-specification-document-set-specification-type').change (function(ev) {
		var fullOptions = (document.getElementById('edit-submitted-specification')).options;
		var selected = ev.target[ev.target.selectedIndex].value;
		var newSelect =  (document.getElementById('edit-submitted-specification-document-set-specification-document'));
		newSelect.options.length = 0;
		for (var ii=0; ii<fullOptions.length; ii++) {
			if (fullOptions[ii].value.substring(0,5) == selected) {
				newSelect.options[newSelect.options.length] = new Option (fullOptions[ii].text, fullOptions[ii].value);
			}
		}
		newSelect = (document.getElementById('edit-submitted-specification-document-set-version'));
		newSelect.options.length = 0;
		newSelect.options[0] = new Option ('Version Not Required', 'N/A');
		if (selected == '19775' || selected == '19776' || selected == '19777') {
			newSelect.options[0] = new Option ('V3.3', 'V3_3', true, true);
			newSelect.options[1] = new Option ('V3.2', 'V3_2');
			newSelect.options[2] = new Option ('V3.1', 'V3_1');
			newSelect.options[3] = new Option ('V3.0', 'V3_0');
		} else if (selected == '19774') {
			newSelect.options[0] = new Option ('V1.0', 'V1_0', true, true);
		} else if (selected == '14772') {
			newSelect.options[0] = new Option ('V2.0', 'V2_0', true, true);
		}
	});
*/

});
;
