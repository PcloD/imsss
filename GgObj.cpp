/*
** Alias Obj �`���̌`��f�[�^
*/
#include "GgObj.h"

// �f�X�g���N�^
gg::GgObj::~GgObj(void)
{
  delete[] group;
  delete[] amb;
  delete[] diff;
  delete[] spec;
  delete[] shi;
}

// �R���X�g���N�^
gg::GgObj::GgObj(const char *name, bool normalize)
{
  // �t�@�C���̓ǂݍ���
  GLuint nv;
  GLfloat (*pos)[3], (*norm)[3];
  ggLoadObj(name, ng, group, amb, diff, spec, shi, nv, pos, norm, normalize);

  // ���_�z��I�u�W�F�N�g�̍쐬
  GLuint vbo[2];
  glGenBuffers(2, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 3 * nv, pos, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 3 * nv, norm, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // ��Ɨp�̃������̉��
  delete[] pos;
  delete[] norm;
}

// �}�`�̕`��
void gg::GgObj::draw(void) const
{
  shader->use();
  use();

  for (unsigned int g = 0; g < ng; ++g)
  {
    shader->setMaterial(amb[g], diff[g], spec[g], shi[g]);
    glDrawArrays(GL_TRIANGLES, group[g][0], group[g][1]);
  }
}
