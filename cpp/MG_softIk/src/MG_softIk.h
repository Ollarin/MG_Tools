#ifndef MG_softIk_H
#define MG_softIk_H

#include <maya/MPxNode.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MTypeId.h>
#include <maya/MPoint.h>

//Class

class MG_softIk : public MPxNode
{
public:
		static void* creator();
 
		MG_softIk();
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);



public:
	/**
	* The node id
	*/
	static MTypeId typeId;
	/**
	* This attribute holds the world matrix of the start reference node of the ik (a transform matching the position of the 
	* ik root
	*/
	static MObject startMatrix;
	/**
	* This attribute holds the world matrix of the end reference node of the ik (a transform matching the position of the 
	* chain last bone
	*/
	static MObject endMatrix;
	/**
	* This attribute is the initial length of the second bone
	*/
	static MObject upInitLength;
	/**
	* This attribute is the initial length of the first bone
	*/
	static MObject downInitLength;
	/**
	* This attribute is the output attribute for the first bone scale 
	*/
	static MObject upScale;
	/**
	* This attribute is the output attribute for the second bone scale
	*/
	static MObject downScale;
	/**
	* This attribute lets you activate smoothly the stretch
	*/
	static MObject stretch;
	/**
	* This attribute define at what distance from straight the ik will start softing
	*/
	static MObject softDistance;
	/**
	* This attribute let you slide the knee up and down
	*/
	static MObject slide;
	/**
	* This is the X component of the output translate array
	*/
	static MObject outputTranslateX;
	/**
	* This is the Y component of the output translate array
	*/
	static MObject outputTranslateY;
	/**
	* This is the Z component of the output translate array
	*/
	static MObject outputTranslateZ;
	/**
	* This is the output translate array
	*/
	static MObject outputTranslate;

private :
	double smoothSthep (double a , double b , double t);


};




#endif 