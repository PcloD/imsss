#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

//
// pass1.vert
//

// �ϊ��s��
uniform mat4 mw;                                                      // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                                      // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                                      // �@���x�N�g���̕ϊ��s��

// ���_����
layout (location = 0) in vec4 pv;                                     // ���[�J�����W�n�̒��_�ʒu
layout (location = 1) in vec4 nv;                                     // ���_�̖@���x�N�g��

// ���X�^���C�U�ɑ��钸�_����
out vec4 p;                                                           // ���̕\�ʏ�̈ʒu P
out vec3 n;                                                           // ���̕\�ʏ�̖@���x�N�g�� N

void main(void)
{
  p = mw * pv;                                                        // �t���O�����g�̈ʒu
  n = normalize((mg * nv).xyz);                                       // �t���O�����g�̖@���x�N�g�� N

  gl_Position = mc * pv;                                              // ���_�ʒu
}
