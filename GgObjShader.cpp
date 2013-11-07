/*
** Alias OBJ �`���̌`��f�[�^�̉A�e�t��
*/
#include "GgObjShader.h"

// �R���X�g���N�^
gg::GgObjShader::GgObjShader(const char *vert, const char *frag,
  const char *geom, GLint nvarying, const char **varyings)
  : GgPointShader(vert, frag, geom, nvarying, varyings)
{
  // �v���O������
  GLuint program = get();

  // �����̃p�����[�^�� uniform �ϐ��̏ꏊ
  loc.pl = glGetUniformLocation(program, "pl");
  loc.lamb = glGetUniformLocation(program, "lamb");
  loc.ldiff = glGetUniformLocation(program, "ldiff");
  loc.lspec = glGetUniformLocation(program, "lspec");

  // �ގ��̃p�����[�^�� uniform �ϐ��̏ꏊ
  loc.kamb = glGetUniformLocation(program, "kamb");
  loc.kdiff = glGetUniformLocation(program, "kdiff");
  loc.kspec = glGetUniformLocation(program, "kspec");
  loc.kshi = glGetUniformLocation(program, "kshi");

  // �ϊ��s��� uniform �ϐ��̏ꏊ
  loc.mg = glGetUniformLocation(program, "mg");
}

// �V�F�[�_�̎g�p�J�n
void gg::GgObjShader::use(void) const
{
  // ���N���X�̃V�F�[�_�̐ݒ���Ăяo��
  GgPointShader::use();

  // ����
  glUniform4fv(loc.pl, 1, l.pos);
  glUniform4fv(loc.lamb, 1, l.amb);
  glUniform4fv(loc.ldiff, 1, l.diff);
  glUniform4fv(loc.lspec, 1, l.spec);

  // �ϊ�
  glUniformMatrix4fv(loc.mg, 1, GL_FALSE, m.g);
}

// �V�F�[�_�̎g�p�I��
void gg::GgObjShader::unuse(void) const
{
  // attribute �ϐ� pv ���o�b�t�@�I�u�W�F�N�g���瓾�邱�Ƃ𖳌��ɂ���
  glDisableVertexAttribArray(1);

  // ���N���X�̃V�F�[�_�̐ݒ���Ăяo��
  GgShader::unuse();
}

// �ϊ��s��̐ݒ�
void gg::GgObjShader::loadMatrix(const GgMatrix &mp, const GgMatrix &mw)
{
  GgPointShader::loadMatrix(mp, mw);
  m.loadNormalMatrix(mw.normal());
}
void gg::GgObjShader::loadMatrix(const GLfloat *mp, const GLfloat *mw)
{
  GgMatrix tmp(mp), tmw(mw);
  loadMatrix(tmp, tmw);
}

// �����ɑ΂��锽�ˌW��
void gg::GgObjShader::setMaterial(const GLfloat *amb, const GLfloat *diff, const GLfloat *spec, GLfloat shi)
{
  glUniform4fv(loc.kamb, 1, amb);
  glUniform4fv(loc.kdiff, 1, diff);
  glUniform4fv(loc.kspec, 1, spec);
  glUniform1f(loc.kshi, shi);
}

