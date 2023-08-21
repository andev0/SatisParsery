#include "MxCellTag.h"

MxCellTag::MxCellTag(const std::string_view parent)
    : XmlElement("mxCell")
{
    setAttribute("id", m_id);

    if (!parent.empty())
    {
        setAttribute("parent", parent);
    }
}

const std::string& MxCellTag::getId() const
{
    return m_id;
}

std::string MxCellTag::generateId()
{
    static size_t index = 0;

    return std::to_string(index++);
}
