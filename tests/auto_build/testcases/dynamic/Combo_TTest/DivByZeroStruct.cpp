/*
 * Copyright 2003-2004 The Apache Software Foundation.

 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains functions to manipulate complex type DivByZeroStruct
 */

#include <axis/AxisWrapperAPI.hpp>
#include <axis/Axis.hpp>

#include "DivByZeroStruct.hpp"

xsd__string DivByZeroStruct::getvarString()
{
	return varString ; 
}

void DivByZeroStruct::setvarString(xsd__string InValue)
{
	varString = InValue ; 
}

xsd__int DivByZeroStruct::getvarInt()
{
	return varInt ; 
}

void DivByZeroStruct::setvarInt(xsd__int InValue)
{
	varInt = InValue ; 
}

xsd__float DivByZeroStruct::getvarFloat()
{
	return varFloat ; 
}

void DivByZeroStruct::setvarFloat(xsd__float InValue)
{
	varFloat = InValue ; 
}
/*
 * This static method serialize a DivByZeroStruct type of object
 */
int Axis_Serialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false)
{
	if ( param == NULL )
	{
	 /* TODO : may need to check nillable value - Now done*/
		pSZ->serializeAsAttribute( "xsi:nil", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);
		pSZ->serialize( ">", NULL);
		return AXIS_SUCCESS;
	}

	/* first serialize attributes if any*/
	if(Axis_URI_DivByZeroStruct)
	{
		bool blnIsNewPrefix = false;
		const AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_DivByZeroStruct, blnIsNewPrefix);
		pSZ->serialize(" xmlns:", sPrefix, "=\"",Axis_URI_DivByZeroStruct, "  \"", NULL);
	}
	pSZ->serialize( ">", 0);

	/* then serialize elements if any*/
	pSZ->serializeAsElement("varString", Axis_URI_DivByZeroStruct, (void*)(param->varString), XSD_STRING);
	pSZ->serializeAsElement("varInt", Axis_URI_DivByZeroStruct, (void*)&(param->varInt), XSD_INT);
	pSZ->serializeAsElement("varFloat", Axis_URI_DivByZeroStruct, (void*)&(param->varFloat), XSD_FLOAT);
	return AXIS_SUCCESS;
}

/*
 * This static method deserialize a DivByZeroStruct type of object
 */
int Axis_DeSerialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapDeSerializer* pIWSDZ)
{
	xsd__string	pValue0 = pIWSDZ->getElementAsString( "varString", 0);

	if( pValue0 == NULL)
	{
		param->varString = NULL;
	}
	else
	{
		param->varString = new char[strlen( pValue0) + 1];
		strcpy( param->varString, pValue0);

		Axis::AxisDelete( (void *) pValue0, XSD_STRING);

	}
	xsd__int * varInt = NULL;

	if ((varInt = pIWSDZ->getElementAsInt( "varInt",0)) != NULL)
	{
		param->varInt = *( varInt );
		Axis::AxisDelete( (void *) varInt, XSD_INT);
	}
	xsd__float * varFloat = NULL;

	if ((varFloat = pIWSDZ->getElementAsFloat( "varFloat",0)) != NULL)
	{
		param->varFloat = *( varFloat );
		Axis::AxisDelete( (void *) varFloat, XSD_FLOAT);
	}
	return pIWSDZ->getStatus();
}
void* Axis_Create_DivByZeroStruct(DivByZeroStruct* pObj, bool bArray = false, int nSize=0)
{
	if (bArray && (nSize > 0))
	{
		if (pObj)
		{
			DivByZeroStruct* pNew = new DivByZeroStruct[nSize];
			size_t i = nSize/2;
			for (int ii=0; ii<i; ++ii)
			{
				pNew[ii] = pObj[ii];
				pObj[ii].reset();
			}
			delete [] pObj;
			return pNew;
		}
		else
		{
			return new DivByZeroStruct[nSize];
		}
	}
	else
		return new DivByZeroStruct;
}

/*
 * This static method delete a DivByZeroStruct type of object
 */
void Axis_Delete_DivByZeroStruct(DivByZeroStruct* param, bool bArray = false, int nSize=0)
{
	if (bArray)
	{
		delete [] param;
	}
	else
	{
		delete param;
	}
}
/*
 * This static method gives the size of DivByZeroStruct type of object
 */
int Axis_GetSize_DivByZeroStruct()
{
	return sizeof(DivByZeroStruct);
}

DivByZeroStruct::DivByZeroStruct()
{
	reset();
}

void DivByZeroStruct::reset()
{
	/*do not allocate memory to any pointer members here
	 because deserializer will allocate memory anyway. */
	memset( &varString, 0, sizeof( xsd__string));
	memset( &varInt, 0, sizeof( xsd__int));
	memset( &varFloat, 0, sizeof( xsd__float));
}

DivByZeroStruct::~DivByZeroStruct() throw ()
{
	/*delete any pointer and array members here*/
	if (varString != NULL)
		delete [] varString;
}
