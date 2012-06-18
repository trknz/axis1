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
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WrapHeaderWriter extends HeaderFileWriter
{
    protected String bindingStyle;
    protected ArrayList methods;
    public WrapHeaderWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext.getServiceInfo().getServicename() + CUtils.WRAPPER_NAME_APPENDER);
        this.wscontext = wscontext;
        this.methods = wscontext.getServiceInfo().getMethods();
        this.bindingStyle = "RPC_ENCODED";
    }

    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            c_writer.write("/*\n");
			c_writer.write(" * Copyright 2003-2006 The Apache Software Foundation.\n\n");
			c_writer.write(" *\n");
			c_writer.write(" * Licensed under the Apache License, Version 2.0 (the \"License\");\n");
			c_writer.write(" * you may not use this file except in compliance with the License.\n");
			c_writer.write(" * You may obtain a copy of the License at\n");
			c_writer.write(" *\n");
			c_writer.write(" *\t\thttp://www.apache.org/licenses/LICENSE-2.0\n");
			c_writer.write(" *\n");
			c_writer.write(" * Unless required by applicable law or agreed to in writing, software\n");
			c_writer.write(" * distributed under the License is distributed on an \"AS IS\" BASIS,\n");
			c_writer.write(" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
			c_writer.write(" * See the License for the specific language governing permissions and\n");
			c_writer.write(" * limitations under the License.\n");
			c_writer.write(" *\n");
            c_writer.write(" * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)\n");
            c_writer.write(" * This file contains Web Service Wrapper declarations\n");
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
            c_writer.write("public:\n\t" + c_classname + "();\n");
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
            c_writer.write("public:\n\tvirtual ~" + c_classname + "();\n");
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
        try
        {
            c_writer.write(
                "public:/*implementation of WrapperClassHandler interface*/\n");
            c_writer.write("\tint AXISCALL invoke(void* pMsg);\n");
            c_writer.write("\tvoid AXISCALL onFault(void* pMsg);\n");
            //writer.write("\tint AXISCALL init();\n");
            //writer.write("\tint AXISCALL fini();\n");
            c_writer.write(
                "\tAXIS_BINDING_STYLE AXISCALL getBindingStyle(){return "
                    + bindingStyle
                    + ";};\n");
            c_writer.write(
                "private:/*Methods corresponding to the web service methods*/\n");
            MethodInfo minfo;
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) methods.get(i);
                c_writer.write(
                    "\tint " + minfo.getSanitizedMethodName() + "(void* pMsg);");
                c_writer.write("\n");
            }

        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            c_writer.write("#include <axis/server/WrapperClassHandler.hpp>\n");
            c_writer.write("#include <axis/IMessageData.hpp>\n");
            c_writer.write("#include <axis/GDefine.hpp>\n");
            c_writer.write("#include <axis/Axis.hpp>\n");
            c_writer.write("#include <axis/AxisWrapperAPI.hpp>\n");
            c_writer.write("#include <axis/OtherFaultException.hpp>\n\n");
            
            c_writer.write("#include \""
                        + CUtils.getWebServiceNameFromWrapperName(c_classname)
                        + CUtils.getHeaderFileExtension()
                        + "\"\n");
            c_writer.write("#include \"AxisServiceException.hpp\" \n\n");
            c_writer.write("AXIS_CPP_NAMESPACE_USE \n\n");
            //writeFaultHeaders();

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
                        "#include \"Axis"
                            + faultInfoName.toString()
                            + "Exception"
                            + CUtils.getHeaderFileExtension()
                            + "\"\n");
                }
            }
            c_writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    protected String getExtendsPart()
    {
        return " : public WrapperClassHandler";
    }
    protected void writeAttributes() throws WrapperFault
    {
        try
        {
            c_writer.write(
                "private:/* Actual web service object*/\n\t"
                    + CUtils.getWebServiceNameFromWrapperName(c_classname)
                    + " *pWs;\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    protected String getFileType()
    {
        return "ServerWrapper";
    }
}
