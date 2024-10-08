#include "set.h"

Set::Set()
{
    //ctor
}

void Set::DoDispose()
{
   m_setZ.clear();
}
vector<int> Set::IntegerToVector(int integer)
{
    vector<int> tempVector;
    tempVector.push_back(integer);
    return tempVector;
}

vector<int> Set::SetDifference(vector<int> setA, vector<int> setB)
{
    bool checkSimilarity;

    DoDispose();

    for( int i = 0 ; i < setA.size() ; i++)
    {
        for(int j = 0 ; j < setB.size() ; j++)
        {
            if(setA[i] == setB[j])
            {
                checkSimilarity = true;
                break;
            }
            else
            {
                checkSimilarity = false;
            }
        }
        if(checkSimilarity == false)
        {
            m_setZ.push_back(setA[i]);
        }
    }
    return m_setZ;

}

vector<int> Set::SetDifference(vector<int> setA, vector<int> setB, vector<int> setC)
{
    vector<int> setD;
    setD = SetDifference(setA, setB);
    m_setZ = SetDifference(setD, setC);
    return m_setZ;
}

vector<int> Set::SetDifference(vector<int> setA, vector<int> setB, vector<int> setC, vector<int> setD)
{
    vector<int> setE;
    setE = SetDifference(setA, setB);
    setE = SetDifference(setE, setC);
    m_setZ = SetDifference(setE, setD);
    return m_setZ;
}

vector<int> Set::SetUnion(vector<int> setA, vector<int> setB)
{
    vector<int> setD;
    bool checkSimilarity;

    DoDispose();

    for( int i = 0 ; i < setA.size() ; i++)
    {
        setD.push_back(setA[i]);
    }

    for(int j = 0 ; j < setB.size() ; j++)
    {
        setD.push_back(setB[j]);
    }

    for(int j = 0 ; j < setD.size() ; j++)
    {
        if(m_setZ.size() == 0)
        {
        m_setZ.push_back(setD[j]);
        }
        else
        {
            for(int k = 0 ; k < m_setZ.size() ; k++)
            {
                if(setD[j] == m_setZ[k])
                {
                    checkSimilarity= true;
                    break;
                }
                else
                {
                    checkSimilarity = false;
                }

            }
            if(checkSimilarity == false)
            {
                m_setZ.push_back(setD[j]);
            }
        }
    }
    return m_setZ;
}

vector<int> Set::SetIntersection(vector<int> setA, vector<int> setB)
{
    bool checkSimilarity;
    DoDispose();

    for( int i = 0 ; i < setA.size() ; i++)
    {
        for(int j = 0 ; j < setB.size() ; j++)
        {
            if(setA[i] == setB[j])
            {
                checkSimilarity = true;
                break;
            }
            else
            {
                checkSimilarity = false;
            }
        }
        if(checkSimilarity == true)
        {
            if(m_setZ.size() == 0)
            {
            m_setZ.push_back(setA[i]);
            }
            else
            {
                for(int k = 0 ; k < m_setZ.size() ; k++)
                {
                    if(setA[i] == m_setZ[k])
                    {
                        checkSimilarity = true;
                        break;
                    }
                    else
                    {
                        checkSimilarity = false;
                    }

                }
                if(checkSimilarity == false)
                {
                    m_setZ.push_back(setA[i]);
                }
            }
        }
    }
    return m_setZ;
}

bool Set::SetIdenticalTest(vector<int> setA, vector<int> setB)
{
    if(setA.size() != setB.size())
    {
        return false;
    }
    else
    {
        vector<int> setC = SetIntersection(setA,setB);
        if(setA.size() == setC.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

vector<int> Set::CreateUniqueVector(vector<int> setA)
{
    DoDispose();
    vector<int>::iterator it;

    sort(setA.begin(), setA.end());
    it = unique(setA.begin(), setA.end());

	setA.resize(std::distance(setA.begin(), it));

	m_setZ = setA;

    return m_setZ;

}

void Set::PrintSet(vector<int> setA)
{
    sort(setA.begin(), setA.end());
    for(int l = 0 ; l < setA.size() ; l++)
    {
    cout << setA[l] << " " ;
    }
    cout << endl;
}



