#pragma once

#include <string>

namespace sigrid{

    class LogicIcon{

        public:

            LogicIcon();
            void setName(const std::string& name);
            std::string getName() const;

            bool operator==(const LogicIcon& rhs) const;
            bool operator!=(const LogicIcon& rhs) const;

        private:
            std::string m_name;
    };

}