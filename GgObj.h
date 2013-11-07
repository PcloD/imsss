#ifndef __GG_OBJ_H__
#define __GG_OBJ_H__

#include "GgObjShader.h"

namespace gg
{
  //
  // Alias OBJ �`���̃t�@�C��
  //
  class GgObj
    : public GgShape
  {
    GLuint ng, (*group)[2];
    GLfloat (*amb)[4], (*diff)[4], (*spec)[4], *shi;
    GgObjShader *shader;

  public:

    // �f�X�g���N�^
    virtual ~GgObj(void);

    // �R���X�g���N�^
    GgObj(const char *name, bool normalize = false);

    // �V�F�[�_�̊��蓖��
    void attachShader(GgObjShader &shader)
    {
      this->shader = &shader;
    }
    void attachShader(GgObjShader *shader)
    {
      this->shader = shader;
    }

    // �}�`�̕`��
    void draw(void) const;
  };

}

#endif
