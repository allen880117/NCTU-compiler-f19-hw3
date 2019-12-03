#include "AST/function.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

FunctionNode::FunctionNode(
    int _line_number, 
    int _col_number, 
    string _function_name, 
    vector<NodeWithTypeList*>* _parameters, 
    VariableInfo* _return_type, 
    Node _body, 
    int _end_line_number, 
    int _end_col_number, 
    string _end_name,
    vector<VariableInfo*> _prototype
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->function_name = _function_name;
        this->parameters = _parameters;
        this->return_type = _return_type;
        this->body = _body;
        this->end_line_number = _end_line_number;
        this->end_col_number = _end_col_number;
        this->prototype = _prototype;
    }

FunctionNode::~FunctionNode(){
    if(this->parameters != nullptr){
        for(uint i=0; i<this->parameters->size(); i++){
            if((*(this->parameters))[i]->node != nullptr)
                delete (*(this->parameters))[i]->node;
            if((*(this->parameters))[i]->type != nullptr)
                delete (*(this->parameters))[i]->type;
            
            delete (*(this->parameters))[i];
        }
        delete this->parameters;
    }
    
    SAFE_DELETE(this->return_type)
    SAFE_DELETE(this->body)

    for(uint i=0; i<this->prototype.size(); i++)
        SAFE_DELETE(this->prototype[i])
}

void FunctionNode::print() {
    std::cout << "function declaration <line: " << line_number
        << ", col: " << col_number
        << "> " << function_name
        << " " ;
    
    // cout << return_type (scalar_type or void)
    switch(this->return_type->type_set){
        case SET_SCALAR:
            switch(this->return_type->type){
                case TYPE_INTEGER: std::cout<<"integer"; break;
                case TYPE_REAL:    std::cout<<"real"; break;
                case TYPE_STRING:  std::cout<<"string"; break;
                case TYPE_BOOLEAN: std::cout<<"boolean"; break;
                default:           std::cout<<"unknown"; break;
            }
            break;
        case UNKNOWN_SET:
            switch(this->return_type->type){
                case TYPE_VOID: std::cout<<"void"; break;
                default:        std::cout<<"unknown"; break;
            }
            break;
        default: std::cout<<"unknown"; break; break;
    }
    // cout << return_type END

    // cout << parameter_prototype
    std::cout<<" (";
        for(uint i=0; i<this->prototype.size(); i++){
            if(i != 0) std::cout<<", ";
            switch(this->prototype[i]->type_set){
                case SET_SCALAR:
                case SET_CONSTANT_LITERAL:
                    switch(this->prototype[i]->type){
                        case TYPE_INTEGER: std::cout<<"integer"; break;
                        case TYPE_REAL:    std::cout<<"real"; break;
                        case TYPE_STRING:  std::cout<<"string"; break;
                        case TYPE_BOOLEAN: std::cout<<"boolean"; break;
                        default:           std::cout<<"unknown"; break;
                    }
                    break;
                case SET_ACCUMLATED:
                    switch(this->prototype[i]->type){
                        case TYPE_INTEGER: std::cout<<"integer"; break;
                        case TYPE_REAL:    std::cout<<"real"; break;
                        case TYPE_STRING:  std::cout<<"string"; break;
                        case TYPE_BOOLEAN: std::cout<<"boolean"; break;
                        default:           std::cout<<"unknown"; break;
                    }

                    for(uint j=0; j<this->prototype[i]->array_range.size(); j++){
                        std::cout<<"[";
                        std::cout<<to_string(this->prototype[i]->array_range[j].end-this->prototype[i]->array_range[j].start);
                        std::cout<<"]";
                    }
                    break;
                default: std::cout<<"unknown"; break;
            }
        }
    std::cout<<")";
    // cout << parameter_prototype END
    std::cout<<std::endl;
}