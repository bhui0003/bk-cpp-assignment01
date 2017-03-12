/*****************************************************************************
Filename: VectorGraphic.cpp
Version: v1.0
Author/Student Name: Brandon Keohane
Student Number: 040719123
Course Name & Number: C++ Programming
Lab Section: 302
Assignment Number: 1
Assignment Name: Vector Graphic in C++
Due Date: 15 October, 2016
Submission Date: 13 October, 2016
Professor Name: A. Tyler
Purpose: Object represents a vector graphic with graphic elements
*****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "Point.h"
#include "Line.h"
#include "GraphicElement.h"
#include "VectorGraphic.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

/*****************************************************************************
Function Name: VectorGraphic Constructor
Purpose: Initializes members of vector graphic
Function In Parameters: Void
Function Out Parameters: Void
Version: v1.0
Author/Student Name: Brandon Keohane
*****************************************************************************/
VectorGraphic::VectorGraphic(){
	numGraphicElements = 0;
	pElements = nullptr;
}

/*****************************************************************************
Function Name: AddGraphicElement
Purpose: Adds graphic element to the vector graphic
Function In Parameters: Void
Function Out Parameters: Void
Version: v1.0
Author/Student Name: Brandon Keohane
*****************************************************************************/
void VectorGraphic::AddGraphicElement(){
	char geName[256];
	int newNumLines, sX, sY, eX, eY, index, newIndex = 0;
	unsigned short outer, inner = 0;

	/* Initialize new temp vector graphic */
	VectorGraphic tmpVG;

	cout << "ADDING a Graphic Element" << endl;
	cout << "Please enter the name of the new GraphicElement(256 characters): ";
	cin >> geName;

	cout << "How many lines are there in the new GraphicElement? ";
	cin >> newNumLines;

	/* Update current size to temp vector graphic */
	tmpVG.numGraphicElements = numGraphicElements + 1;

	/* Malloc enough space for another graphic element to be added to temp vector graphic */
	if ((tmpVG.pElements = new GraphicElement[tmpVG.numGraphicElements]) == NULL){
		cout << "InitVectorGraphic malloc failed" << endl;
		return;
	}

	/* Add old Graphic Elements to the new dynamically allocated array */
	for (outer = 0; outer < numGraphicElements; ++outer){

		/* Copy num lines */
		tmpVG.pElements[outer] = pElements[outer];

		/* Allocate new line pointer to perform deep copy further in loop */
		if ((tmpVG.pElements[outer].pLines = new Line[pElements[outer].numLines]) == NULL){
			cout << "Could not allocat enough memory for Line Pointer";
			return;
		}

		/* Get deep copy of Lines to temp vector graphic */
		for (inner = 0; inner < pElements[outer].numLines; ++inner){
			tmpVG.pElements[outer].pLines[inner] = pElements[outer].pLines[inner];
		}
		
	}

	/* Delete all elements from last one */
	delete []pElements;

	/*
	Set new index variable for readability
	num elements = 2 new index = 1 in dynamically allocated array
	*/
	newIndex = tmpVG.numGraphicElements - 1;

	/* Set number of lines in the new graphic element */
	tmpVG.pElements[newIndex].numLines = newNumLines;

	/* Set name of graphic element */
	strcpy(tmpVG.pElements[newIndex].name, geName);

	/* Allocate new line pointer */
	if ((tmpVG.pElements[newIndex].pLines = new Line[newNumLines]) == NULL){
		cout << "Could not allocat enough memory for Line Pointer";
		return;
	}

	/* Add new Graphic Element */
	for (index = 0; index < newNumLines; ++index){
		/* For some reason this was giving warning if they were not initialized, but they are at the beginning... */
		sX, sY, eX, eY = 0;
		/* Get all the coordinates for the line */
		cout << "Please enter the x coord of the start point of line index " << index << ": ";
		cin >> sX;
		cout << "Please enter the y coord of the start point of line index " << index << ": ";
		cin >> sY;
		cout << "Please enter the x coord of the end point of line index " << index << ": ";
		cin >> eX;
		cout << "Please enter the y coord of the end point of line index " << index << ": ";
		cin >> eY;

		/* Enter all coordinates into newly allocated line */
		tmpVG.pElements[newIndex].pLines[index].start.x = sX;
		tmpVG.pElements[newIndex].pLines[index].start.y = sY;
		tmpVG.pElements[newIndex].pLines[index].end.x = eX;
		tmpVG.pElements[newIndex].pLines[index].end.y = eY;
	}

	/*
		Add temp elements array with old and new elements back into this objects array and update size
	*/

	/* Add newly allocated memory to original object */
	pElements = new GraphicElement[tmpVG.numGraphicElements];

	for (outer = 0; outer < tmpVG.numGraphicElements; ++outer){

		/* Copy new graphic elements data */
		pElements[outer] = tmpVG.pElements[outer];

		/* Allocate for new lines */
		pElements[outer].pLines = new Line[tmpVG.pElements[outer].numLines];

		/* Get all lines from temp vector graphic */
		for (inner = 0; inner < tmpVG.pElements[outer].numLines; ++inner){
			pElements[outer].pLines[inner] = tmpVG.pElements[outer].pLines[inner];
		}

	}

	/* Update Graphic Element count in original object */
	numGraphicElements = tmpVG.numGraphicElements;
}

/*****************************************************************************
Function Name: DeleteGraphicElement
Purpose: Deletes a graphic element specified by user from array
Function In Parameters: Void
Function Out Parameters: Void
Version: v1.0
Author/Student Name: Brandon Keohane
*****************************************************************************/
void VectorGraphic::DeleteGraphicElement(){
	int iCount = 0;
	unsigned short iOuter, iInner, index = 0;
	VectorGraphic tmpVG;

	/* If there are no graphic elements in vector graphic return */
	if (numGraphicElements == 0) {
		cout << "No Elements to delete." << endl;
		return;
	}

	cout << "Please enter the index of the Graphic Element you wish to delete: ";
	cin >> index;

	/* Must be a valid index */
	if (index > numGraphicElements - 1 || index < 0){
		cout << "Must be an index from 0 to " << numGraphicElements - 1 << ", try again." << endl;
		return;
	}

	/* Allocate for new array */
	tmpVG.pElements = new GraphicElement[numGraphicElements - 1];
	/* Update number of graphic elements to be copied */
	tmpVG.numGraphicElements = numGraphicElements - 1;

	/* Loop and grab all elements except the one to delete */
	for (iOuter = 0; iOuter < numGraphicElements; ++iOuter){

		/* Skip index to delete */
		if (iOuter == index) continue;

		/* Places graphic element into correct spot */
		tmpVG.pElements[iCount] = pElements[iOuter];

		// Allocate for new lines
		tmpVG.pElements[iCount].pLines = new Line[pElements[iOuter].numLines];

		// Deep copy old lines
		for (iInner = 0; iInner < pElements[iOuter].numLines; ++iInner){
			tmpVG.pElements[iCount].pLines[iInner] = pElements[iOuter].pLines[iInner];
		}

		/* Increment where to add element */
		iCount++;
	}

	delete []pElements;

	/* Add newly allocated memory to original object */
	pElements = new GraphicElement[tmpVG.numGraphicElements];

	/* Deep copy new array into main object */
	for (iOuter = 0; iOuter < tmpVG.numGraphicElements; ++iOuter){

		/* Get info about graphic element */
		pElements[iOuter] = tmpVG.pElements[iOuter];

		/* Allocate for new lines */
		pElements[iOuter].pLines = new Line[tmpVG.pElements[iOuter].numLines];

		/* Deep copy lines */
		for (iInner = 0; iInner < tmpVG.pElements[iOuter].numLines; ++iInner){
			pElements[iOuter].pLines[iInner] = tmpVG.pElements[iOuter].pLines[iInner];
		}

	}

	/* Update Graphic Element count in original object */
	numGraphicElements = tmpVG.numGraphicElements;
}

/*****************************************************************************
Function Name: ReportVectorGraphic
Purpose: Reports all vector graphics to standard out
Function In Parameters: Void
Function Out Parameters: Void
Version: v1.0
Author/Student Name: Brandon Keohane
*****************************************************************************/
void VectorGraphic::ReportVectorGraphic(){
	unsigned int in, out, numL = 0;

	/* Header */
	cout << "Vector Graphic Report" << endl;

	/* Loops through all graphic elements */
	for (out = 0; out < numGraphicElements; ++out){

		cout << "Reporting Graphic Element #" << out << endl;
		cout << "Graphic Element name: " << pElements[out].name << endl;

		/* Holds number of lines for graphic element */
		numL = pElements[out].numLines;

		/* Loops through all lines in graphic element */
		for (in = 0; in < numL; ++in){
			/* Gets the line and then the memory location to that line and frees allocated memory */
			printf("Line #%d start x: %d\n", in, pElements[out].pLines[in].start.x);
			printf("Line #%d start y: %d\n", in, pElements[out].pLines[in].start.y);
			printf("Line #%d end x: %d\n", in, pElements[out].pLines[in].end.x);
			printf("Line #%d end y: %d\n", in, pElements[out].pLines[in].end.y);
		}

	}
}