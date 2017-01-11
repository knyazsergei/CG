#include "stdafx.h"
#include "Light.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace
{
}

CAbstractLightSource::CAbstractLightSource(unsigned index)
	: m_index(index)
{
}

CAbstractLightSource::~CAbstractLightSource()
{
}

glm::vec4 CAbstractLightSource::GetAmbient() const
{
	return m_ambient;
}

glm::vec4 CAbstractLightSource::GetDiffuse() const
{
	return m_diffuse;
}

glm::vec4 CAbstractLightSource::GetSpecular() const
{
	return m_specular;
}

void CAbstractLightSource::SetAmbient(const glm::vec4 &color)
{
	m_ambient = color;
}

void CAbstractLightSource::SetDiffuse(const glm::vec4 &color)
{
	m_diffuse = color;
}

void CAbstractLightSource::SetSpecular(const glm::vec4 &color)
{
	m_specular = color;
}

void CAbstractLightSource::SetupImpl() const
{
	// �������� �������� ����� � �������� ��������.
	// �������� ��������� ������ ����� ������� ����� GL_LIGHTING!
	glEnable(GLenum(m_index));
	glLightfv(m_index, GL_AMBIENT, glm::value_ptr(m_ambient));
	glLightfv(m_index, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glLightfv(m_index, GL_SPECULAR, glm::value_ptr(m_specular));
}

unsigned CAbstractLightSource::GetIndex() const
{
	return m_index;
}

CDirectedLightSource::CDirectedLightSource(unsigned index)
	: CAbstractLightSource(index)
	, m_direction(0, 0, 0, 0)
{
}

glm::vec3 CDirectedLightSource::GetDirection() const
{
	return{ m_direction.x, m_direction.y, m_direction.z };
}

void CDirectedLightSource::SetDirection(const glm::vec3 &value)
{
	m_direction.x = value.x;
	m_direction.y = value.y;
	m_direction.z = value.z;
}

void CDirectedLightSource::Setup() const
{
	SetupImpl();
	// ���� GL_POSITION ���������� ��� (x, y, z, 0), �.�. ��� ������
	// � ���������� �����������, �������� ����� ����� ������������.
	glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(m_direction));
}

CPositionLightSource::CPositionLightSource(unsigned index)
	: CAbstractLightSource(index)
	, m_position(0, 0, 0, 1)
{
}

glm::vec3 CPositionLightSource::GetPosition() const
{
	return{ m_position.x, m_position.y, m_position.z };
}

void CPositionLightSource::SetPosition(const glm::vec3 &value)
{
	m_position.x = value.x;
	m_position.y = value.y;
	m_position.z = value.z;
}

void CPositionLightSource::Setup() const
{
	SetupImpl();
	// ���� GL_POSITION ���������� ��� (x, y, z, 1), �.�. ��� �����
	// � ���������� �����������, �������� ����� ����� ��������.
	glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(m_position));
}

void CPhongModelMaterial::Setup() const
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}

glm::vec4 CPhongModelMaterial::GetEmission() const
{
	return m_emission;
}

void CPhongModelMaterial::SetEmission(const glm::vec4 &emission)
{
	m_emission = emission;
}

glm::vec4 CPhongModelMaterial::GetAmbient() const
{
	return m_ambient;
}

void CPhongModelMaterial::SetAmbient(const glm::vec4 &ambient)
{
	m_ambient = ambient;
}

glm::vec4 CPhongModelMaterial::GetDiffuse() const
{
	return m_diffuse;
}

void CPhongModelMaterial::SetDiffuse(const glm::vec4 &diffuse)
{
	m_diffuse = diffuse;
}

glm::vec4 CPhongModelMaterial::GetSpecular() const
{
	return m_specular;
}

void CPhongModelMaterial::SetSpecular(const glm::vec4 &specular)
{
	m_specular = specular;
}

float CPhongModelMaterial::GetShininess() const
{
	return m_shininess;
}

void CPhongModelMaterial::SetShininess(float shininess)
{
	m_shininess = shininess;
}