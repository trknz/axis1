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

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include "NCName.hpp"

AXIS_CPP_NAMESPACE_START

NCName::NCName()
{}

NCName::NCName(const xsd__NCName value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE NCName::getType()
{
    return XSD_NCNAME;
}

xsd__NCName NCName::getNCName()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeNCName(m_Buf);
    }
}

void * NCName::getValue()
{
    return (void*) getNCName();
}

xsd__NCName NCName::deserializeNCName(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (xsd__NCName) deserializeName(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
