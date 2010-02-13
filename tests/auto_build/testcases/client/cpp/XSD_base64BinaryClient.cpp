// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO THIS FILE MAY ALSO REQUIRE CHANGES TO THE               */
/* C-EQUIVALENT FILE. PLEASE ENSURE THAT IT IS DONE.                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


#include "XSD_base64Binary.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"


int main(int argc, char* argv[])
{
    XSD_base64Binary* ws;
    
    xsd__base64Binary input;
    xsd__base64Binary result;
    xsd__base64Binary* nillableResult;
    
    xsd__unsignedByte* testUB;
    
    int size = 0;
    const xsd__unsignedByte * resultData;   
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_base64Binary";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        ws = new XSD_base64Binary(endpoint);

        testUB = (xsd__unsignedByte*)stringToAscii("<test><xml>some dod&y string</xml></test>");
        input.set(testUB, 41);

        // Test non-nillable element
        result = ws->asNonNillableElement(input);
        resultData = result.get(size);
        
        cout << "non-nillable element" << endl;
        cout << " size=" << size << endl;
        cout << " data=" << asciiToStringOfLength((char *)resultData, size) << endl;

        // Test nillable element, with a value
        nillableResult = ws->asNillableElement(&input);
        if (nillableResult)
        {
            cout << "nillable element" << endl;
            resultData = nillableResult->get(size);
            cout << " size=" << size << endl;
            cout << " data=" << asciiToStringOfLength((char *)resultData, size) << endl;
            delete nillableResult;
        }
        else
            cout << "nillable element=<nil>" << endl;

        // Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
        if (nillableResult)
        {
            cout << "nillable element" << endl;
            resultData = nillableResult->get(size);
            cout << " size=" << size << endl;
            cout << " data=" << asciiToStringOfLength((char *)resultData, size) << endl;
            delete nillableResult;
        }
        else
            cout << "nil element=<nil>" << endl;

        // Test array
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsd__base64Binary_Array arrayInput;
        xsd__base64Binary_Array* arrayResult;
        xsd__base64Binary *array[ARRAY_SIZE];
        const xsd__base64Binary **output;
        
        for (i=0 ; i < 2 ; i++)
            array[i] =new xsd__base64Binary(input);
            
        arrayInput.set(array,ARRAY_SIZE);
        
        arrayResult = ws->asArray(&arrayInput);
        
        if (arrayResult)
            output=arrayResult->get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (i = 0; i < outputSize ; i++)
        {
            resultData = output[i]->get(size);
            cout << " element[" << i << "]" << endl;
            cout << "  size=" << size << endl;
            cout << "  data=" << asciiToStringOfLength((char *) resultData, size) << endl;
        }

        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            delete array[i];
        delete arrayResult;

        // Test complex type
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.setcomplexTypeElement(input);
        complexTypeResult = ws->asComplexType(&complexTypeInput);
        xsd__base64Binary binaryObject = complexTypeResult->getcomplexTypeElement();
        resultData = binaryObject.get(size);
        cout << "within complex type" << endl;
        cout << " size=" << size << endl;
        cout << " data=" << asciiToStringOfLength((char *)resultData, size) << endl;
        delete complexTypeResult;

        // Tests now complete

        delete ws;
    }
    catch(AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << "Unknown exception has occured: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }

    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}

