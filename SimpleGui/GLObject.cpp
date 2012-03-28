#include "GLObject.h"
#include "GLWindow.h"

std::map<int,GLObject*>   g_mObjects; // map of id to objects
int                       g_nHandleCounter;

/////////////////////////////////////////////////////////////////////////////////
GLObject::GLObject()
{
    m_bVisible = true;
}

/////////////////////////////////////////////////////////////////////////////////
// set the parent window pointer
void GLObject::InitWindowPtr( GLWindow* pWin )
{
    _RecursivelyInitObjects( this, pWin  );
}

/////////////////////////////////////////////////////////////////////////////////
GLWindow* GLObject::Window()
{
    return m_pWin;
}

/////////////////////////////////////////////////////////////////////////////////
void GLObject::SetVisible()
{
    m_bVisible = true;
}

/////////////////////////////////////////////////////////////////////////////////
void GLObject::SetInVisible()
{
    m_bVisible = false;
}

/////////////////////////////////////////////////////////////////////////////////
bool GLObject::IsVisible()
{
    return m_bVisible;
}

/////////////////////////////////////////////////////////////////////////////////
void GLObject::SetName( const std::string& sName )
{
    m_sObjectName = sName;
}

/////////////////////////////////////////////////////////////////////////////////
const char* GLObject::ObjectName()
{
    return m_sObjectName.c_str();
}

/////////////////////////////////////////////////////////////////////////////////
void GLObject::SetId( unsigned int nId )
{
    m_nId = nId;
}

/////////////////////////////////////////////////////////////////////////////////
unsigned int GLObject::Id()
{
    return m_nId;
}

/////////////////////////////////////////////////////////////////////////////////
int GLObject::WindowWidth()
{
    return m_pWin->w();
}

/////////////////////////////////////////////////////////////////////////////////
int GLObject::WindowHeight()
{
    return m_pWin->h();
}

/////////////////////////////////////////////////////////////////////////////////
bool GLObject::IsSelected( unsigned int nId )
{
    return m_pWin->IsSelected( nId );
}

/////////////////////////////////////////////////////////////////////////////////
void GLObject::UnSelect( unsigned int nId )
{
    m_pWin->UnSelect( nId );
}

/////////////////////////////////////////////////////////////////////////////////
unsigned int GLObject::AllocSelectionId()
{
    unsigned int nId =  m_pWin->AllocSelectionId( this );
    return nId;
}

/////////////////////////////////////////////////////////////////////////////////
Eigen::Vector3d GLObject::GetPosUnderCursor()
{
    return m_pWin->GetPosUnderCursor();
}

/////////////////////////////////////////////////////////////////////////////////
Eigen::Vector2i GLObject::GetCursorPos()
{
    return m_pWin->GetCursorPos();
}

/////////////////////////////////////////////////////////////////////////////////
bool GLObject::valid()
{
    if( m_pWin && m_pWin->valid() ) {
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////
void GLObject::AddChild( GLObject* pChild )
{
    m_vpChildren.push_back( pChild );
    pChild->m_pParent = this;
    g_mObjects[ g_nHandleCounter ] = pChild;
    pChild->SetId( g_nHandleCounter ); 
    g_nHandleCounter++;

}


///////////////////////////////////////////////////////////////////////////////////////////////
void  GLObject::_RecursivelyInitObjects( GLObject* pObj, GLWindow* pWin )
{
    m_pWin = pWin;
    for( size_t ii = 0; ii < pObj->m_vpChildren.size(); ii++ ){
        _RecursivelyInitObjects( pObj->m_vpChildren[ii], pWin );
    }
}

