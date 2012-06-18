/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubHeaderWriter extends HeaderFileWriter
{
    protected ArrayList methods;
    public ClientStubHeaderWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext.getServiceInfo().getServicename());
        this.wscontext = wscontext;
        this.methods = wscontext.getServiceInfo().getMethods();
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            c_writer.write("/*\n");
            c_writer.write(" * This file was auto-generated by the Axis C++ Web Service "
                    + "Generator (WSDL2Ws)\n");
            c_writer.write(" * This file contains Client Stub Class for remote web service \n");
            c_writer.write(" */\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
     */
    protected void writeConstructors() throws WrapperFault
    {
        try
        {
            c_writer.write(
                "public:\n\tSTORAGE_CLASS_INFO " + c_classname
                    + "(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol=APTHTTP1_1);\n");
            c_writer.write("\tSTORAGE_CLASS_INFO " + c_classname + "();\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
     */
    protected void writeDestructors() throws WrapperFault
    {
        try
        {
            c_writer.write("public:\n\tSTORAGE_CLASS_INFO virtual ~" + c_classname + "();\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        MethodInfo minfo;

        try
        {
            c_writer.write("public: \n");
            
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                
                //write return type
                if (0 == noOfOutParams)
                    c_writer.write("\tSTORAGE_CLASS_INFO void ");
                else if (1 == noOfOutParams)
                {
                    ParameterInfo returnParam =
                        (ParameterInfo) minfo.getOutputParameterTypes().iterator().next();
                    String outParamTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(returnParam, wscontext);
                    if ((CUtils.isArrayType(outParamTypeName))
                            || (CUtils.isSimpleType(outParamTypeName)
                                && (returnParam.isNillable() || returnParam.isOptional())
                                && !(CUtils.isPointerType(outParamTypeName))))
                        c_writer.write("\tSTORAGE_CLASS_INFO " + outParamTypeName + " * ");
                    else
                        c_writer.write("\tSTORAGE_CLASS_INFO " + outParamTypeName + " ");
                }
                else
                {
                    isAllTreatedAsOutParams = true;
                    c_writer.write("\tSTORAGE_CLASS_INFO void ");
                }                
                //write return type
                c_writer.write(minfo.getSanitizedMethodName() + "(");

                //write parameter names 
                Iterator params = minfo.getInputParameterTypes().iterator();
                String commaSeperator = "";
                for (int j = 0; params.hasNext(); j++)
                {
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(nparam, wscontext);
                    if ((CUtils.isArrayType(paramTypeName))
                            || (CUtils.isSimpleType(paramTypeName)
                                    && (nparam.isNillable() || nparam.isOptional())
                                    && !(CUtils.isPointerType(paramTypeName))))
                        c_writer.write(commaSeperator + paramTypeName + " * Value" + j);
                    else
                        c_writer.write(commaSeperator + paramTypeName + " Value" + j);
                    
                    if (j==0)
                        commaSeperator = ", ";
                }
                
                if (isAllTreatedAsOutParams)
                {
                    params = minfo.getOutputParameterTypes().iterator();
                    for (int j = 0; params.hasNext(); j++)
                    {
                        ParameterInfo nparam = (ParameterInfo) params.next();
                        c_writer.write(", AXIS_OUT_PARAM "
                                + CUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext)
                                + " *OutValue"
                                + j);
                    }
                }
                c_writer.write(");\n");
            }
        }
        catch (Exception e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
     * TODO: Not sure why this method should not be the same as the one in literal/ directory - 
     *       that is, move the one in literal dir here and remove it from literal/ClientStubHeaderWriter.java
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            c_writer.write("#include <axis/client/Stub.hpp>\n");
            c_writer.write("#include <axis/OtherFaultException.hpp>\n");
            c_writer.write("#include <axis/ISoapAttachment.hpp>\n");
            c_writer.write("#include <axis/ISoapFault.hpp>\n");
            c_writer.write("\n");
            c_writer.write("AXIS_CPP_NAMESPACE_USE\n");
            c_writer.write("\n");
            
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            HashSet typeSet = new HashSet();
            HashSet removeSet = new HashSet();
            String typeName = null;
            
            while (types.hasNext())
            {
                atype = (Type) types.next();
                if (atype.isAnonymous() && !atype.isExternalized())
                    continue;

                typeName = CUtils.getLanguageTypeName4Type(atype);
                if (null != typeName)
                    typeSet.add(typeName);
          
                if (atype.isRestriction())
                    removeSet.add(CUtils.getArrayNameForType(atype.getLanguageSpecificName()));                
            }
            
            Iterator ritr = removeSet.iterator();
            while (ritr.hasNext())
                typeSet.remove(ritr.next());
            
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                c_writer.write("#include \"" + itr.next().toString() + CUtils.getHeaderFileExtension() + "\"\n");
            }
            
            //Method to print the Fault Exception headers
            //writeFaultHeaders();
            c_writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
     */
    protected void writeFaultHeaders() throws WrapperFault
    {
        try
        {

            MethodInfo minfo;
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) methods.get(i);
                Iterator fault = minfo.getFaultType().iterator();
                String faultInfoName = null;
                while (fault.hasNext())
                {
                    FaultInfo info = (FaultInfo) fault.next();
                    faultInfoName = info.getFaultInfo();
                    c_writer.write(
                        "#include \"Axis" + faultInfoName.toString()
                            + "Exception" + CUtils.getHeaderFileExtension() + "\"\n");
                }
                c_writer.write("\n");
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected String getFileType()
    {
        return "ClientStub";
    }

    protected String getExtendsPart()
    {
        return " :public Stub";
    }
}
