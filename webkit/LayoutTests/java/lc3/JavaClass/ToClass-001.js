/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 1997, 1998 Netscape Communications Corporation.
 * Copyright (C) 2010 Apple Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * ***** END LICENSE BLOCK ***** */

gTestfile = 'ToClass-001.js';

/**
 *  JavaScript to Java type conversion.
 *
 *  This test passes JavaScript number values to several Java methods
 *  that expect arguments of various types, and verifies that the value is
 *  converted to the correct value and type.
 *
 *  This tests instance methods, and not static methods.
 *
 *  Running these tests successfully requires you to have
 *  com.netscape.javascript.qa.liveconnect.DataTypeClass on your classpath.
 *
 *  Specification:  Method Overloading Proposal for Liveconnect 3.0
 *
 *  @author: christine@netscape.com
 *
 */
var SECTION = "JavaClass to java.lang.Class";
var VERSION = "1_4";
var TITLE   = "LiveConnect 3.0 JavaScript to Java Data Type Conversion " +
  SECTION;
startTest();

var dt = applet.createQAObject("com.netscape.javascript.qa.liveconnect.DataTypeClass");

var a = new Array();
var i = 0;

// Extract the corresponding Java class object

a[i++] = new TestObject (
  "var newClass = java.lang.Class.forName(\"java.lang.Byte\"); "+
  "dt.setClass( newClass )",
  "dt.PUB_CLASS",
  "dt.instanceGetClass()",
  "dt.instanceGetClass()",
  'java.lang.Class.forName("java.lang.Byte")',
  '"object"' );

// pass a java class to a method that expects a java.lang.Object

a[i++] = new TestObject (
  "var newClass = java.lang.Class.forName(\"java.lang.Byte\"); "+
  "var javaVector = new java.util.Vector() ;"+
  "javaVector.addElement( newClass ); " +
  "javaVector.elementAt(0)",
  "dt.PUB_CLASS",
  "dt.instanceGetClass()",
  "dt.instanceGetClass()",
  'java.lang.Class.forName("java.lang.Byte")',
  '"object"' );


for ( i = 0; i < a.length; i++ ) {

  try {
    eval(a[i].jsValue);
  } catch (ex) {
    testFailed(a[i].jsValue + ": " + ex);
    continue;
  }

  shouldBeWithErrorCheck(
    a[i].description +"; "+ a[i].javaFieldName,
    a[i].jsValue);

  shouldBeWithErrorCheck(
    a[i].description +"; " + a[i].javaMethodName,
    a[i].jsValue);

  shouldBeWithErrorCheck(
    a[i].javaTypeName,
    a[i].jsType);
}

function TestObject( description, javaField, javaMethod, javaType,
                     jsValue, jsType )
{
  this.description = description;
  this.javaFieldName = javaField;
  this.javaMethodName = javaMethod;
  this.javaTypeName = javaType,

  this.jsValue   = jsValue;
  this.jsType      = jsType;
}
