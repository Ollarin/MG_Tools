#include "curveNode.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MMatrix.h>


  

MTypeId curveNode::typeId( 0x832414 );




MObject curveNode::inputMatrix;
MObject curveNode::output;
MObject curveNode::degree;
MObject curveNode::transformMatrix;





//Class


void* curveNode::creator()
{

	return new curveNode();
}

MStatus curveNode::initialize()
	{  
		//This is the curve degree attribute
		MFnNumericAttribute numFn;
		degree = numFn.create("degree","d",MFnNumericData::kInt,3);
		numFn.setMin(1);
		addAttribute(degree);
	
		//Those are all the matrix input 

		MFnMatrixAttribute    matrixFn;
		inputMatrix =matrixFn.create("inputMatrix","im");
		matrixFn.setArray(true);
		matrixFn.setStorable(true);
		addAttribute(inputMatrix); 

		//This is the curve's matrix used to compensate curve translate

		transformMatrix =matrixFn.create("transformMatrix","tm");
		matrixFn.setStorable(true);
		addAttribute(transformMatrix); 


		//This is the curve output attribute
		MFnTypedAttribute typedFn;

		output  = typedFn.create("output","o",MFnData::kNurbsCurve);
		typedFn.setStorable(false);
		typedFn.setWritable(false);
		addAttribute(output);

		attributeAffects(degree,output);
		attributeAffects(inputMatrix,output);
		attributeAffects(transformMatrix,output);

		return MS::kSuccess;
	}
MStatus curveNode::compute(const MPlug& plug,MDataBlock& dataBlock)
	{

		if (plug==output)
		{
			
			//MStatus
			MStatus stat;


			//Point array for the curve
			MPointArray pointArray ;

			//Get data from inputs
			MDataHandle degreeH = dataBlock.inputValue(degree);
			int degreeValue = degreeH.asInt();

			MDataHandle tmH = dataBlock.inputValue(transformMatrix);
			MMatrix tm = tmH.asMatrix();


			MArrayDataHandle inputMatrixH = dataBlock.inputArrayValue(inputMatrix);
			inputMatrixH.jumpToArrayElement(0);
			//Loop to get matrix data and convert in points

			for (int unsigned i=0;i<inputMatrixH.elementCount();i++,inputMatrixH.next())
			{
				

				MMatrix currentMatrix = inputMatrixH.inputValue(&stat).asMatrix() ;
				
				//Compensate the locator matrix
				
				MMatrix fixedMatrix = currentMatrix*tm.inverse();
				MPoint matrixP (fixedMatrix[3][0],fixedMatrix[3][1],fixedMatrix[3][2]);
				pointArray.append(matrixP);
				
			}
			
		MFnNurbsCurve curveFn;
		MFnNurbsCurveData curveDataFn;
		MObject curveData= curveDataFn.create();

		curveFn.createWithEditPoints(pointArray,degreeValue,MFnNurbsCurve::kOpen,0,0,0,curveData,&stat);
		
		MDataHandle outputH = dataBlock.outputValue(output);
		outputH.set(curveData);
		outputH.setClean();

		}


		return MS::kSuccess;
	}





