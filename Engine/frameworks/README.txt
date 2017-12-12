To compile a shared framework, use the following commands
cd ${frameworkName} && g++ -fPIC -shared Framework${FrameworkName}.cpp -I../../includes -std=c++11 -o ${frameworkName}.so

(please pay attention to the capitalization of the first letter of the framework name variable [${FrameworkName} is not the same than ${frameworkName}])
