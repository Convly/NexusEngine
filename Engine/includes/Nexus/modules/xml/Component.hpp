#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Integrity.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{

    class Component{
    public:
        static std::vector<env::ScriptComponent> getScripts(env::Environment& env, const GameInfosParser& gameInfosParser, xml_node<>* rootNode, std::string& error, bool onlyOneScript){
            std::vector<env::ScriptComponent> scripts;

            for (xml_node<>* node = rootNode->first_node("Script"); node; node = node->next_sibling("Script")){
                std::unordered_map<std::string, std::string> attributes;

                attributes.clear();
                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::ScriptComponent script(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            script.getEntityInfos().setActive(Integrity::boolValue(attribute.second, error));
                        else if (attribute.first == "path")
                            script.setScriptPath(Integrity::path(env, gameInfosParser.getFields()._resources.at("scripts"), attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in a script tag \"" + attributes.at("name") + "\"\n";
                    }
                    if (onlyOneScript && scripts.size() >= 1)
                        error += "Error: You can't have more than one script. \"" + script.getEntityInfos().getName() + "\" is too much\n";
                    else
                        scripts.push_back(script);
                }
            }
            if (onlyOneScript && scripts.empty())
                scripts.push_back(env::ScriptComponent(""));
            return scripts;
        }

        static std::vector<env::TransformComponent> getTransforms(xml_node<>* rootNode, std::string& error, bool onlyOneTransform){
            std::vector<env::TransformComponent> transforms;

            for (xml_node<>* node = rootNode->first_node("Transform"); node; node = node->next_sibling("Transform")){
                std::unordered_map<std::string, std::string> attributes;

                attributes.clear();
                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::TransformComponent transform(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            transform.getEntityInfos().setActive(Integrity::boolValue(attribute.second, error));
                        else if (attribute.first == "pos")
                            transform.setPos(Integrity::pos(attribute.second, error));
                        else if (attribute.first == "rotation")
                            transform.setRotation(Integrity::intValue(attribute.second, error));
                        else if (attribute.first == "size")
                            transform.setSize(Integrity::xyValues(attribute.second, error));
                        else if (attribute.first == "direction")
                            transform.setDirection(Integrity::xyValues(attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this transform tag \"" + attributes.at("name") + "\"\n";
                    }
                    if (onlyOneTransform && transforms.size() >= 1)
                        error += "Error: You can't have more than one transform. \"" + transform.getEntityInfos().getName() + "\" is too much\n";
                    else
                        transforms.push_back(transform);
                }
            }
            if (onlyOneTransform && transforms.empty())
                transforms.push_back(env::TransformComponent(""));
            return transforms;
        }

        static std::vector<env::RendererComponent> getRenderers(env::Environment& env, const GameInfosParser& gameInfosParser, xml_node<>* rootNode, std::string& error, bool onlyOneRenderer){
            std::vector<env::RendererComponent> renderers;

            for (xml_node<>* node = rootNode->first_node("Renderer"); node; node = node->next_sibling("Renderer")){
                std::unordered_map<std::string, std::string> attributes;

                attributes.clear();
                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::RendererComponent renderer(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            renderer.getEntityInfos().setActive(Integrity::boolValue(attribute.second, error));
                        else if (attribute.first == "opacity")
                            renderer.setOpacity(Integrity::opacity(attribute.second, error));
                        else if (attribute.first == "texturePath")
                            renderer.setTexturePath(Integrity::path(env, gameInfosParser.getFields()._resources.at("images"), attribute.second, error));
                        else if (attribute.first == "shapeType")
                            renderer.setShapeType(Integrity::shapeType(attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this renderer tag \"" + attributes.at("name") + "\"\n";
                    }
                    if (onlyOneRenderer && renderers.size() >= 1)
                        error += "Error: You can't have more than one renderer. \"" + renderer.getEntityInfos().getName() + "\" is too much\n";
                    else
                        renderers.push_back(renderer);
                }
            }
            if (onlyOneRenderer && renderers.empty())
                renderers.push_back(env::RendererComponent(""));
            return renderers;
        }

        static std::vector<env::RigidBodyComponent> getRigidBodies(xml_node<>* rootNode, std::string& error, bool onlyOneRigidBody){
            std::vector<env::RigidBodyComponent> rigidBodies;

            for (xml_node<>* node = rootNode->first_node("RigidBody"); node; node = node->next_sibling("RigidBody")){
                std::unordered_map<std::string, std::string> attributes;

                attributes.clear();
                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::RigidBodyComponent rigidBody(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            rigidBody.getEntityInfos().setActive(Integrity::boolValue(attribute.second, error));
                        else if (attribute.first == "mass")
                            rigidBody.setMass(Integrity::doubleValue("mass", attribute.second, error));
                        else if (attribute.first == "bounciness")
                            rigidBody.setBounciness(Integrity::doubleValue("bounciness", attribute.second, error));
                        else if (attribute.first == "size")
                            rigidBody.setSize(Integrity::xyValues(attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this rigidBody tag \"" + attributes.at("name") + "\"\n";
                    }
                    if (onlyOneRigidBody && rigidBodies.size() >= 1)
                        error += "Error: You can't have more than one rigidBody. \"" + rigidBody.getEntityInfos().getName() + "\" is too much\n";
                    else
                        rigidBodies.push_back(rigidBody);
                }
            }
            if (onlyOneRigidBody && rigidBodies.empty())
                rigidBodies.push_back(env::RigidBodyComponent(""));
            return rigidBodies;
        }
    };

}
}

#endif