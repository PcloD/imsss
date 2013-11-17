#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

#define REFLECTIVE_OCCLUSION 0

//
// pass2.frag
//

const float PI = 3.141593;                                            // �~����
const int MAXSAMPLES = 256;                                           // �T���v���_�̍ő吔
const float kshi = 60.0;                                              // �P���W��

uniform int samples;                                                  // �T���v���_��
uniform float radius;                                                 // �T���v���_�̎U�z���a
uniform float translucency;                                           // �������x
uniform vec4 ambient;                                                 // �������x
uniform vec4 mapping;                                                 // �e�N�X�`�����W�̃X�P�[���ƃI�t�Z�b�g
uniform sampler2D unit[6];                                            // �e�N�X�`�����j�b�g
uniform vec4 point[MAXSAMPLES];                                       // �T���v���_�̈ʒu

// �ϊ��s��
uniform mat4 mp;                                                      // ���e�ϊ��s��
uniform mat4 mr;                                                      // �����ʃ}�b�s���O�p
uniform mat4 mt;                                                      // �e�N�X�`���̉�]

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec2 tc;                                                           // �e�N�X�`�����W

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                                    // �t���O�����g�̐F

void main(void)
{
  // ���˃}�b�v�̃e�X�g�p
  //fc = texture(unit[5], tc * mapping.xy + mapping.zw);
  //return;

  // unit[0] ���� albedo ���擾
  vec4 albedo = texture(unit[0], tc);

  // albedo �̃A���t�@�l�� 0 �Ȃ�w�i�F
  if (albedo.a == 0.0)
  {
    fc = vec4(0.0);
    return;
  }

  // unit[1] ���� fresnel ���擾
  vec4 fresnel = texture(unit[1], tc);

  // unit[2] ���珈���Ώۂ̉�f�̎��_���W�n��̈ʒu���擾
  vec4 position = texture(unit[2], tc);

  // unit[3] ���珈���Ώۂ̉�f�̎��_���W�n��̖@���x�N�g�����擾 (w = 0)
  vec3 normal = texture(unit[3], tc).xyz;

  // �����x�N�g��
  vec3 view = normalize(position.xyz);

  // ���˃x�N�g��
  vec3 reflection = (vec4(reflect(view, normal), 0.0) * mt).xyz;

  // normal �����̕��ˏƓx
  vec4 diffuse = vec4(0.0);

  // reflection �����̕��ˏƓx
#if REFLECTIVE_OCCLUSION
  vec4 specular = vec4(0.0);
#else
  vec4 specular = mix(ambient, texture(unit[5], (reflection.xz * 0.5 / (1.0 + reflection.y) + 0.5) * mapping.xy + mapping.zw), step(0.0, reflection.y));
#endif

  // �Օ�����Ȃ��|�C���g�̐�
  float count = 0.0;

  // �X�̃T���v���_�ɂ���
  for (int i = 0; i < samples; ++i)
  {
    // �T���v���_�̑��Έʒu
    vec4 offset = vec4(radius * point[i].w * point[i].xyz, 0.0);

    // �T���v���_�̈ʒu�� p ����̑��Έʒu�ɕ��s�ړ�������C���̓_�̃N���b�s���O���W�n��̈ʒu q �����߂�
    vec4 q = mp * (position + offset);

    // �e�N�X�`�����W�ɕϊ�����
    q = q * 0.5 / q.w + 0.5;

    // q �̐[�x�� unit[4] �̒l (�f�v�X�o�b�t�@�̒l) ��菬������Ή��W�� visibility = 0 �傫����� visibility = 1
    float visibility = step(q.z, texture(unit[4], q.xy).x);

    // ���W���̑��a�����߂�
    count += visibility;

    //if (visibility == 0.0) continue;  // �����L���ɂ���� 15% ���炢�x���Ȃ�

    // �V��}�b�v�̃T���v�����O���������߂�
    vec4 v = mt * point[i];

    // �����ʃ}�b�v����V��̕��ˋP�x�𓾂� (v.y < 0 �Ȃ�����ʃ}�b�v�̊O��������w�i�F)
    vec4 radiance = mix(ambient, texture(unit[5], (v.xz * 0.5 / (1.0 + v.y) + 0.5) * mapping.xy + mapping.zw), step(0.0, v.y)) * visibility;
  
    // normal �����̕��ˏƓx�̏d�݂Â��a�����߂�
    diffuse += max(dot(v.xyz, normal), 0.0) * radiance;

#if REFLECTIVE_OCCLUSION
    // reflection �����̕��ˏƓx�̏d�݂Â��a�����߂�
    specular += pow(max(dot(v.xyz, reflection), 0.0), kshi) * radiance;
#endif
  }

  // normal �����̕��ˏƓx�𐳋K������
  diffuse *= 4.0 / float(samples);

#if REFLECTIVE_OCCLUSION
  // reflection �����̕��ˏƓx�𐳋K������
  specular *= (kshi + 8.0) / float(samples);
#endif

  // �`�B�x
  //float transmission = count / samples;
  //float transmission = 1.0 - sin(sqrt(2.0 * (samples - count) / samples) * PI * 0.5);
  float transmission = 2.0 * exp(-sin(sqrt(2.0 * (samples - count) / samples) * PI * 0.5));

  // �A���x�h
  //fc = albedo;

  // �t���l��
  //fc = fresnel;

  // ���ˏƓx
  //fc = diffuse;

  // �f�荞��
  //fc = specular;

  // �ʒu
  //fc = position * 0.5 + 0.5;

  // �@��
  //fc = vec4(normal * 0.5 + 0.5, 1.0);

  // �[�x
  //fc = vec4(texture(unit[4], tc).r);

  // �`�B�x
  //fc = vec4(transmission);

  // �V�󂩂�̕��ˏƓx�ɂ�鎩�ȎՕ����l�������A�e
  //fc = albedo * diffuse;

  // �A�e�ɓ`�B�x��ώZ
  fc = albedo * mix(diffuse, ambient * transmission, translucency);

  // �A���x�h�~���ˏƓx�Ɖf�荞�݂���z��
  fc = mix(fc, specular, fresnel);
}
