#!/usr/bin/env python

import sys
import os
import re

def createClassH(path, classname):
    context = ""
    context += "#ifndef SHREK_" + classname.upper() + "_H" + "\n"
    context += "#define SHREK_" + classname.upper() + "_H" + "\n"
    context += "" + "\n"
    context += "#include <common/Common.h>" + "\n"
    context += "" + "\n"
    context += "namespace shrek {\n" #begin namespace
    context += "" + "\n"
    context += "class " + classname + "\n"
    context += "{" + "\n"
    context += "public:" + "\n"
    context += "    " + classname + "();" + "\n"
    context += "    ~" + classname + "();" + "\n"
    context += "private:" + "\n"
    context += "    " + classname + "(const " + classname + " &);" + "\n"
    context += "    " + classname + "& operator=(const " + classname + " &);" + "\n"
    context += "public:" + "\n"
    context += "" + "\n"
#    context += "private:" + "\n"
#    context += "    SHREK_LOG_DECLARE();" + "\n"
    context += "};" + "\n"
    context += "" + "\n"
    context += "SHREK_TYPEDEF_PTR(" + classname +");" + "\n\n"
    context += "}\n" #end namespace
    context += "" + "\n"
    context += "#endif //SHREK_" + classname.upper() + "_H" + "\n"
    f = file(path + "/" + classname + ".h", "w")
    f.write(context)
    f.close()
    return True

def createClassCPP(path, classname):
    context = ""
    context += "#include <" + classname + ".h>" + "\n"
    context += "" + "\n"
    context += "using namespace std;\n"
    context += "using namespace std::tr1;\n"
    context += "namespace shrek {\n" #begin namespace
#    context += "SHREK_LOG_SETUP(" + ns + ", " + classname + ");" + "\n"
    context += "" + "\n"
    context += classname + "::" + classname + "() { " + "\n"
    context += "}" + "\n"
    context += "" + "\n"
    context += classname + "::~" + classname + "() { " + "\n"
    context += "}" + "\n"
    context += "" + "\n"
    context += "}\n" #end namespace
    context += "" + "\n"
    f = file(path + "/" + classname + ".cpp", "w")
    f.write(context)
    f.close()
    return True

def createClass(path, classname):
    ret = 0
    if os.path.exists(path + "/" + classname + ".h"):
        print "header file " + path + "/" + classname + ".h exists!" 
    else:
        if createClassH(path, classname):
            print "create header file " + path + "/" + classname + ".h succeed."
            ret = ret + 1
        else:
            print "create header file " + path + "/" + classname + ".h failed."
    if os.path.exists(path + "/" + classname + ".cpp"):
        print "source file " + path + "/" + classname + ".cpp exists!" 
    else:
        if createClassCPP(path, classname):
            print "create source file " + path + "/" + classname + ".cpp succeed."
            ret = ret + 1
        else:
            print "create source file " + path + "/" + classname + ".cpp failed."
    return ret

def insertSConscript(scon_name, name):
    hasFindSource = False
    hasWritten = False
    os.system("mv " + scon_name + " " + scon_name + ".bak")
    TIP = ur"sources\s*=\s*\["
    fin = file(scon_name + ".bak", "r");
    fout = file(scon_name, "w");
    while True:
        l = fin.readline()
        if not l:
            break;
        if not hasFindSource and not hasWritten:
            if re.search(TIP, l):
                hasFindSource = True
        elif not hasWritten and l.find(']') != -1:
            l = "    \'" + name + ".cpp\',\n" + l
            hasFindSource = False
            hasWritten = True
        fout.write(l)
    fin.close()
    fout.close()
    print name + " has been inserted into " + scon_name
    os.system("rm " + scon_name + ".bak")
    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print >> sys.stderr, "Usage:", sys.argv[0], "<classname>"
        sys.exit(1)
    path = os.getcwd()
    if createClass(path, sys.argv[1]) == 2:
        insertSConscript(path + "/SConstruct", sys.argv[1])
#           insertMakefile(path + "/Makefile.am", sys.argv[1])
