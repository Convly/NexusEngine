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
        static std::vector<env::ScriptComponent> getScripts(env::Environment& env, xml_node<>* rootNode, std::string& error){
            std::vector<env::ScriptComponent> scripts;

            for (xml_node<>* node = rootNode->first_node("Script"); node; node = node->next_sibling("Script")){
                std::unordered_map<std::string, std::string> attributes;

                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::ScriptComponent script(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            script.getEntityInfos().setActive(Integrity::active(attribute.second, error));
                        else if (attribute.first == "paths")
                            script.setScriptPath(Integrity::path(env, attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this script tag \"" + attributes.at("name") + "\"\n";
                    }
                    scripts.push_back(script);
                }
            }
            return scripts;
        }

        static std::vector<env::TransformComponent> getTransforms(xml_node<>* rootNode, std::string& error){
            std::vector<env::TransformComponent> transforms;

            for (xml_node<>* node = rootNode->first_node("Transform"); node; node = node->next_sibling("Transform")){
                std::unordered_map<std::string, std::string> attributes;

                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::TransformComponent transform(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            transform.getEntityInfos().setActive(Integrity::active(attribute.second, error));
                        else if (attribute.first == "pos")
                            transform.setPos(Integrity::pos(attribute.second, error));
                        else if (attribute.first == "rotation")
                            transform.setRotation(Integrity::rotation(attribute.second, error));
                        else if (attribute.first == "size")
                            transform.setSize(Integrity::size(attribute.second, error));
                        else if (attribute.first == "direction")
                            transform.setDirection(Integrity::direction(attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this transform tag \"" + attributes.at("name") + "\"\n";
                    }
                    transforms.push_back(transform);
                }
            }
            return transforms;
        }

        static std::vector<env::RendererComponent> getRenderers(env::Environment& env, xml_node<>* rootNode, std::string& error){
            std::vector<env::RendererComponent> renderers;

            for (xml_node<>* node = rootNode->first_node("Renderer"); node; node = node->next_sibling("Renderer")){
                std::unordered_map<std::string, std::string> attributes;

                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::RendererComponent renderer(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            renderer.getEntityInfos().setActive(Integrity::active(attribute.second, error));
                        else if (attribute.first == "opacity")
                            renderer.setOpacity(Integrity::opacity(attribute.second, error));
                        else if (attribute.first == "texturePath")
                            renderer.setTexturePath(Integrity::texturePath(env, attribute.second, error));
                        else if (attribute.first == "shapeType")
                            renderer.setShapeType(Integrity::shapeType(attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this renderer tag \"" + attributes.at("name") + "\"\n";
                    }
                    renderers.push_back(renderer);
                }
            }
            return renderers;
        }

        static std::vector<env::RigidBodyComponent> getRigidBodies(xml_node<>* rootNode, std::string& error){
            std::vector<env::RigidBodyComponent> rigidBodies;

            for (xml_node<>* node = rootNode->first_node("RigidBody"); node; node = node->next_sibling("RigidBody")){
                std::unordered_map<std::string, std::string> attributes;

                if ((error += Util::getAttributes(node->name(), node, attributes)).empty()){
                    env::RigidBodyComponent rigidBody(attributes.at("name"));

                    for (auto attribute : attributes){
                        if (attribute.first == "name");
                        else if (attribute.first == "active")
                            rigidBody.getEntityInfos().setActive(Integrity::active(attribute.second, error));
                        else if (attribute.first == "mass")
                            rigidBody.setMass(Integrity::doubleValue("mass", attribute.second, error));
                        else if (attribute.first == "bounciness")
                            rigidBody.setBounciness(Integrity::doubleValue("bounciness", attribute.second, error));
                        else if (attribute.first == "size")
                            rigidBody.setSize(Integrity::size(attribute.second, error));
                        else
                            error += "Error: This attribute can't be created in this rigidBody tag \"" + attributes.at("name") + "\"\n";
                    }
                    rigidBodies.push_back(rigidBody);
                }
            }
            return rigidBodies;
        }
    };

}
}

#endif