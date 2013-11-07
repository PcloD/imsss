#ifndef __GG_SIMPLESHADER_H__
#define __GG_SIMPLESHADER_H__

/*
** Alias OBJ �`���̌`��f�[�^�̉A�e�t��
*/
#include "GgPointShader.h"

namespace gg
{
  class GgObjShader
    : public GgPointShader
  {
    // ����
    struct
    {
      GLfloat pos[4];   // �����ʒu
      GLfloat amb[4];   // �������x�̊�������
      GLfloat diff[4];  // �������x�̊g�U���ˌ�����
      GLfloat spec[4];  // �������x�̋��ʔ��ˌ�����
    } l;

    // �ϊ�
    struct
    {
      GLfloat g[16];    // ���f���r���[�ϊ��̖@���ϊ��s��
      void loadNormalMatrix(const GgMatrix &m) { m.get(g); }
    } m;

    // �ꏊ
    struct
    {
      GLint pl;         // �����ʒu�� uniform �ϐ��̏ꏊ
      GLint lamb;       // �������x�̊��������� uniform �ϐ��̏ꏊ
      GLint ldiff;      // �������x�̊g�U���ˌ������� uniform �ϐ��̏ꏊ
      GLint lspec;      // �������x�̋��ʔ��ˌ������� uniform �ϐ��̏ꏊ
      GLint kamb;       // �����̔��ˌW���� uniform �ϐ��̏ꏊ
      GLint kdiff;      // �g�U���ˌW���� uniform �ϐ��̏ꏊ
      GLint kspec;      // ���ʔ��ˌW���� uniform �ϐ��̏ꏊ
      GLint kshi;       // �P���W���� uniform �ϐ��̏ꏊ
      GLint mg;         // ���f���r���[�ϊ��̖@���ϊ��s��� uniform �ϐ��̏ꏊ
    } loc;

  public:

    // �f�X�g���N�^
    virtual ~GgObjShader(void) {}

    // �R���X�g���N�^
    GgObjShader(void) {}
    GgObjShader(const char *vert, const char *frag = 0,
      const char *geom = 0, GLint nvarying = 0, const char **varyings = 0);
    GgObjShader(const GgObjShader &o)
      : GgPointShader(o), l(o.l), m(o.m), loc(o.loc) {}

    // ���
    GgObjShader &operator=(const GgObjShader &o)
    {
      if (&o != this)
      {
        GgPointShader::operator=(o);
        l = o.l;
        m = o.m;
        loc = o.loc;
      }
      return *this;
    }

    // �V�F�[�_�̎g�p�J�n
    virtual void use(void) const;

    // �V�F�[�_�̎g�p�I��
    virtual void unuse(void) const;

    // �����̈ʒu
    void setLightPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      l.pos[0] = x;
      l.pos[1] = y;
      l.pos[2] = z;
      l.pos[3] = w;
    }
    void setLightPosition(const GLfloat *pos)
    {
      setLightPosition(pos[0], pos[1], pos[2], pos[3]);
    }

    // �������x�̊�������
    void setLightAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      l.amb[0] = r;
      l.amb[1] = g;
      l.amb[2] = b;
      l.amb[3] = a;
    }
    void setLightAmbient(const GLfloat *amb)
    {
      setLightAmbient(amb[0], amb[1], amb[2], amb[3]);
    }

    // �������x�̊g�U���ˌ�����
    void setLightDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      l.diff[0] = r;
      l.diff[1] = g;
      l.diff[2] = b;
      l.diff[3] = a;
    }
    void setLightDiffuse(const GLfloat *diff)
    {
      setLightDiffuse(diff[0], diff[1], diff[2], diff[3]);
    }

    // �������x�̋��ʔ��ˌ�����
    void setLightSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      l.spec[0] = r;
      l.spec[1] = g;
      l.spec[2] = b;
      l.spec[3] = a;
    }
    void setLightSpecular(const GLfloat *spec)
    {
      setLightSpecular(spec[0], spec[1], spec[2], spec[3]);
    }

    // �����ɑ΂��锽�ˌW��
    void setMaterial(const GLfloat *amb, const GLfloat *diff, const GLfloat *spec, GLfloat shi);

    // �ϊ��s��̐ݒ�
    virtual void loadMatrix(const GgMatrix &mp, const GgMatrix &mw);
    virtual void loadMatrix(const GLfloat *mp, const GLfloat *mw);
  };

}

#endif
