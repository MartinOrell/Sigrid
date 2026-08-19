#include "sigrid/Window/WorkWindow/WorkWindowContainer.h"

#include <iostream>

bool sigrid::WorkWindowContainer::load(sigrid::InputStream& is){

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardContainer: Failed to read string."
                << " Failed to load BoardContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "["){
            continue;
        }
        else if(s == "]"){
            break;
        }
        else if(s == "boardColumns:"){

            const auto columns_o = is.readInt();
            if(columns_o == std::nullopt){

                std::cerr << "WorkWindowContainer: Failed to read BoardColumns."
                    << " Failed to load WorkWindowContainer" << std::endl;
                return false;
            }
            this->boardColumns = columns_o.value();
        }
        else if(s == "boardRows:"){

            const auto rows_o = is.readInt();
            if(rows_o == std::nullopt){

                std::cerr << "WorkWindowContainer: Failed to read BoardRows."
                    << " Failed to load WorkWindowContainer" << std::endl;
                return false;
            }
            this->boardRows = rows_o.value();
        }
        else{
            std::cerr << "WorkWindowContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load WorkWindowContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::WorkWindowContainer::getString(const int& indentLevel) const{

    sigrid::String columnsString;
    columnsString.set(std::to_string(this->boardColumns));

    sigrid::String rowsString;
    rowsString.set(std::to_string(this->boardRows));

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("boardColumns: ");
    out.append(columnsString);

    out.append("\n");
    out.append(indent1);
    out.append("boardRows: ");
    out.append(rowsString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}