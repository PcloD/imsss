#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

//
// pass2.vert
//

// ���_����
layout (location = 0) in vec4 pv;                                     // ���[�J�����W�n�̒��_�ʒu

// ���X�^���C�U�ɑ��钸�_����
out vec2 tc;                                                          // �e�N�X�`�����W

void main(void)
{
  tc = pv.xy * 0.5 + 0.5;
  gl_Position = pv;
}
