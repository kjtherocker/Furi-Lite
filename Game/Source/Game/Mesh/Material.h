#ifndef __Material_H__
#define __Material_H__

class ShaderProgram;

class Material
{
protected:
    ShaderProgram* m_pShader;
    MyColor m_Color;
    GLuint m_Texture;

public:
	Material() {}
	Material(ShaderProgram* pShader, GLuint texture)
	{
		m_pShader = pShader;
		m_Texture = texture;
	}

    ShaderProgram* GetShader() { return m_pShader; }
    MyColor GetColor() { return  m_Color; }
	GLuint GetTexture() { return  m_Texture; }
	void SetTexture(GLuint Tex) { m_Texture = Tex; }
};

#endif //__Material_H__
