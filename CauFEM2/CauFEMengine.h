#ifndef __CAU_FEM_ENGINE_H__
#define __CAU_FEM_ENGINE_H__
// ���� : FEM ����
// �ۼ��� : ���¿�
// �ۼ��� : 2005.7.24

#include <AfxTempl.h>

// Constance define 
//
#define MAX_DEF_STR	256
#define DEF_METRIX_SIZE 6	// �ӽ÷� 3d truss�� ����.
#define FEM_ERROR_VALUE -1.

#define _BooLeq(c1, c2)	(fabs((c1) - (c2)) < 1.0E-6)
#define _BooLz(v1)		(fabs(v1) < 1.0E-6)
#define _POW2(v)	(v * v)

// FemVector class
//
#define MAX_DIM 3
class FemVector
{
public:
	FemVector();
	~FemVector();

public:
	double v[MAX_DIM];
};


// FemMetrix class
//
class FemEngine;
class FemElement;
class FemMetrix
{
public:
	FemMetrix(int iSize = DEF_METRIX_SIZE);
	virtual ~FemMetrix();
	void Dump();

	void Resize(int iSize);
	void Clear();
	int GetSize();

	void SetAt(int i, int j, double dValue);
	double GetAt(int i, int j);
	void SetFreeDegreeAt(int i, int iFreeDegree, bool bFixed);
	int GetFreeDegreeAt(int i);
	bool GetFixedAt(int i);
	bool GetFreeDegreePos(int& iRow, int& iCol);

	FemMetrix& operator*=(double dScalar);
	FemVector& operator*(FemVector& v);

	void CopyFrom(double aaMetrix[DEF_METRIX_SIZE][DEF_METRIX_SIZE]);
	void CopyFrom(FemMetrix& Src);
	void SetSymmetry();
	void Inverse();	// K^-1

public:
	bool Add(int i, int j, double& dValue);
	bool Add(FemMetrix& m);

	void Reduce();
	int GetReduceFreeDegreeSize();

private:
	int m_iSize;

	#define MAX_METRIX_SIZE 128
	double* m_pMetrix[MAX_METRIX_SIZE];
	bool m_abFixed[MAX_METRIX_SIZE];
	int m_aiFreeDegree[MAX_METRIX_SIZE];
};


// FemVertex class
//
class FemVertex
{
public:
	FemVertex(FemEngine* pEngine);
	~FemVertex();

	void SetFixed(int iIndex, bool bFixed);
	bool IsFixed(int iIndex);
	void SetCoord(int iIndex, double dValue);
	double GetCoord(int iIndex);
	void SetForce(int iIndex, double dForce);
	double GetForce(int iIndex);

	double GetLength(FemVertex* pVertex);
	enum AxisPlaneType
	{
		eAxisX = 0,
		eAxisY,
		eAxisZ
	};
	double GetCosineAt(int iAxis, FemVertex* pVertex);

	virtual void Dump();

protected:
	bool m_abFixed[MAX_DIM];	// ��������
	double m_aCoord[MAX_DIM];	// ��ǥ
	double m_aForce[MAX_DIM];	// �ܷ�
	// double m_aMoment[MAX_DIM];	// 

	FemEngine* m_pEngine;
};

// class FemElement
//
class FemElement
{
public:
	FemElement(FemEngine* pEngine);
	~FemElement();

	enum MaturialType
	{
		eElastic = 0,	// ź��
		eArea = 1,		// ����
		eMaxMaturial	
	};
	void SetMaturial(FemElement::MaturialType eType, double dValue);
	virtual bool GetK(FemMetrix& mK);
	virtual bool GetForce(FemVector& vForce);

	virtual void Dump();

protected:
	double m_adMaturial[FemElement::eMaxMaturial];
	FemMetrix m_m;

	FemEngine* m_pEngine;
};

// FemBeamElement class
//
// class FemBeamElement : public FemElement
// {
// public:
// 	virtual bool GetK(FemMetrix& mK);
// };

// FemBarElement class
//
// #define MAX_BAR_VERTEX 2;
// class FemBarElement : public FemElement		// ��
// {
// public:
// 	virtual bool GetK(FemMetrix& mK);
// 
// private:
// 	int m_aVertex[MAX_BAR_VERTEX];
// };

// FemBeamElement class
//
// class FemBeamElement : public FemElement	// ��
// {
// public:
// 	virtual bool GetK(FemMetrix& mK);
// };
// 

// FemTrussElement class
//
class FemTrussElement : public FemElement	// Ʈ����Ʈ
{
public:
	FemTrussElement(FemEngine* pEngine);

	void SetVertex(int iNo, int iVertex);
	int GetVertexIndex(int iNo);
	FemVertex* GetVertex(int iNo);

	double GetLength();
	double GetCosineAt(int iAxis);

	virtual bool GetK(FemMetrix& mK);

private:
	int m_aVertexIndex[2];
};

// FemSolid class
//
// class FemSolidElement : public FemElement
// {
// public:
// 	FemSolid();
// 	
// 	void DivideElement();	// ��Һ���
// }
 
// FemEngine class
//
#define MAX_FEM_VERTEX  200
#define MAX_FEM_ELEMENT 100
class FemEngine	// Vertex ���. 2���� ������ ���� �������.
{
public:
	FemEngine();
	~FemEngine();

	bool Init();
	bool Load(const char* szInputFile);
	void Action();
	void Save(const char* szOutputFile);

	bool AddVertex(FemVertex* pVertex);
	int GetVertexCount();
	FemVertex* GetVertexAt(int iIndex);
	void ClearVertex();

	bool AddElement(FemElement* pEle);
	int GetElementCount();
	FemElement* GetElementAt(int iIndex);
	void ClearElement();

protected:
	virtual bool Solve(FemMetrix& FullMetrix, FemVector& vDelta);
	virtual void GetForce(FemMetrix& mK, FemVector &vForce);	// F = Kd ���� d�� ���

private:
	CString m_sTitle;
	CArray<FemVertex*, FemVertex*> m_aVertex;
	CArray<FemElement*, FemElement*> m_aElement;
};


// �۾� ��ȹ
//
// 1. ���� p154�� ������ Ʈ���� FEM�� �����.
// 2. 1 �ϼ��� �̸� ������� ��� ������/���� �ؼ� FEM�� �����.
// 3. 2D �ﰢ�� �������� FEM�� �����.
//
  
#endif
