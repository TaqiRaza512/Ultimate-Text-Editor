#pragma once
#include<iostream>
#include<fstream>
#include <string>
using namespace std;

void gotoRowCol(int rpos, int cpos);

class Line
{
	friend class TextEditor;
	friend class Document;
	char* Cs;
	int Size=0; 
public:
	Line()
	{
		Cs = new char[1] {};
		Size = 0;
	}
	Line(const Line& AL)
	{
		Cs = new char[AL.Size + 1];
		Size = AL.Size;
		for (int ri=0;ri<=AL.Size;ri++)
		{
			Cs[ri]=AL.Cs[ri];				
		}
	}
	void InsertCharAt(int i,char ch)
	{
		char* HA = new char[Size+2];
		for (int ci=0;ci<i;ci++)
		{
			HA[ci] = Cs[ci];			
		}
		HA[i] = ch;

		for (int ci=i;ci<=Size;ci++)
		{
			HA[ci + 1] = Cs[ci];  
		}
		delete[] Cs;
		Cs = HA;
		Size++;
	}
	void OverlapChar(int i,int ch)
	{
		Cs[i] = ch;
	}
	void DeleteACharAt(int i)
	{
		char* HA = new char[Size];
		for (int ci = 0, h = 0; ci <= Size; ci++, h++)
		{
			if (ci == i)
			{
				ci++;
			}
			HA[h] = Cs[ci];
		}
		delete[]Cs;
		Cs = HA;
		Size--;
	}	
	~Line()
	{
		//delete[]Cs;
	}
};
class Document
{
	friend class TextEditor;
	friend class Line;
	Line* Ls;
	int NofLs;
	string DName;
public:
	Document(const string& dname)
	{
		NofLs = 0;
		Load(dname); 
	}
	int Size_String(string ch)
	{
		int size = 0;
		for (int i=0;ch[i]!='\0';i++)
		{
			size++;
		}
		return size;
	}
	void Load(string fname)
	{
		DName = fname;
		ifstream Rdr(DName);
		Rdr >> NofLs;
		Rdr.ignore();
		Ls = new Line[NofLs];
		int ri = 0, ci = 0;
		char ch;
		while (true)
		{
			ch = Rdr.get();
			if (!Rdr)
			{
				break;
			}
			if(ch == '\n')
			{
				ri++;
				ci = 0;
			}
			else
			{
				InsertACharacter(ri, ci, ch);
				ci++;
			}
		}
	}
	void InsertACharacter(int li,int ci,int ch)
	{
		Ls[li].InsertCharAt(ci, ch);
	}	
	void DeleteACharAt(int li,int ci)
	{
		Ls[li].DeleteACharAt(ci - 1);
	}
	void MergeTheLine(int li, int ci)
	{
		Line Lm;
		
		int Size = Ls[li].Size + Ls[li - 1].Size;
	
		for (int ri=0;ri<Ls[li-1].Size;ri++)
		{
			Lm.InsertCharAt(ri, Ls[li-1].Cs[ri]);
		}
		for (int i=Ls[li-1].Size,j=0;i<=Size;i++,j++)
		{
			Lm.InsertCharAt(i, Ls[li].Cs[j]);
		}
		Line* HLs = new Line[NofLs-1];
		for (int ri = 0, h = 0; ri < NofLs-1; ri++, h++)
		{
			if (ri == li-1)
			{
				HLs [h] = Lm;
				h++;
				for (int i=ri+1;i< NofLs-1;i++,h++)
				{
					HLs[h] = Ls[i+1];
				}
				break;

			}
			else
			{
				HLs[h] = Ls[ri];
			}
		}
		delete[]Ls;
		Ls = HLs;
		NofLs--;
	}
	void TO_Upper(int li,int ci)
	{
		int left=ci,size=0;
		while (true)
		{
			if (Ls[li].Cs[left]==32)
			{

				break;
			}
			if (left==0)
			{
				left--;
				break;
			}
			size++;
			left--;
		}
		int right = ci+1;
		while (true)
		{
			if (Ls[li].Cs[right] == 32 or Ls[li].Cs[right]=='.' or Ls[li].Cs[right]==10)
			{
				break;
			}

			size++;
			right++;
		}		
		for (int i=left+1;i<right;i++)
		{

			if (isalpha(Ls[li].Cs[i]))
			{
				if (islower(Ls[li].Cs[i]))
				{
					Ls[li].Cs[i] = toupper(Ls[li].Cs[i]);
				}
			}
			Ls[li].OverlapChar(i, Ls[li].Cs[i]);
		}
	}
	void TO_Lower(int li,int ci)
	{

		int left = ci, size = 0;
		while (true)
		{
			if (Ls[li].Cs[left] == 32)
			{

				break;
			}
			if (left == 0)
			{
				left--;
				break;
			}
			size++;
			left--;
		}
		int right = ci + 1;
		while (true)
		{
			if (Ls[li].Cs[right] == 32 or Ls[li].Cs[right] == '.' or Ls[li].Cs[right] == 10)
			{
				break;
			}

			size++;
			right++;
		}
		for (int i = left + 1; i < right; i++)
		{

			if (isalpha(Ls[li].Cs[i]))
			{
				if (isupper(Ls[li].Cs[i]))
				{
					Ls[li].Cs[i] = tolower(Ls[li].Cs[i]);
				}
			}
			Ls[li].OverlapChar(i, Ls[li].Cs[i]);
		}
	}
	void InsertANewLineAt(int li,int ci)
	{
		Line Lo, Ln;
		int lfi = 0;
		for (int ri=0;ri<ci;ri++)
		{
			Lo.InsertCharAt(lfi, Ls[li].Cs[ri]);
			lfi++;
		}
		int lni = 0;
		for (int i=ci;i<Ls[li].Size;i++)
		{
			Ln.InsertCharAt(lni, Ls[li].Cs[i]);
			lni++;
		}

		Line* HLs = new Line[NofLs + 1];

		for (int ri=0,h=0;ri<NofLs;ri++,h++)
		{
			if (ri==li)
			{				
				HLs[h] = Lo;
				h++;
				HLs[h] = Ln;		
			}
			else
			{
				HLs[h] = Ls[ri];
			}
		}
		delete[]Ls;
		Ls = HLs;
		NofLs++;

	}
	void PrintDocument()
	{
		system("cls");
		for (int ri=0;ri<NofLs;ri++)
		{
			cout << Ls[ri].Cs << endl;
		}
	}
	void PrintDocumentFile()
	{
		ofstream Wrt(DName);

		Wrt << NofLs << endl;
		for (int ri = 0; ri < NofLs; ri++)
		{
			Wrt << Ls[ri].Cs << endl;
		}

	}
	void MatchA_Word_Case_Sensitive(int &li,int &ci,string ch)
	{
		int size = Size_String(ch);
		int count = 0,match_count=0;
		for (int i=0;i<NofLs;i++)
		{
			for (int r=0;r<Ls[i].Size;r++)
			{
				
					for (int j=r-size+1,k=0;j<=r;j++,k++)
					{
						if (!(Ls[i].Cs[j]==ch[k]))
						{
							match_count = 0;
							break;
						}
						else
						{
							match_count++;
						}

						if (match_count==size && Ls[i].Cs[j-match_count]==32 && Ls[i].Cs[r+1]==32)
						{
							li = i;
							ci = r - size + 1;
							return;
						}
						else if (match_count == size && Ls[i].Cs[j-match_count] == 32 && Ls[i].Cs[j + 1] =='.')
						{
							li = i;
							ci = r - size + 1;
							return;
						}
						else if(match_count == size && j -match_count+1==0  && Ls[i].Cs[r + 1] == 32)
						{
							li = i;
							ci = r - size + 1;
							return;
						}
						else if (match_count == size && Ls[i].Cs[j - match_count]== 32 && Ls[i].Cs[r + 1] == '\0')
						{
							li = i;
							ci = r - size + 1;
							return;
						}
						else if (match_count == size && j - match_count+1 ==0  && Ls[i].Cs[r + 1] == '\0')
						{
							li = i;
							ci = r - size + 1;
							return;
						}
					}	
					if (!(match_count == size))
					{
						match_count = 0;
					}
					count = 0;								
			}
			
		}

	}
	void MatchA_Word_Case_InSensitive(int& li, int& ci, string ch)
	{
		int size = Size_String(ch);
		int count = 0, match_count = 0;
		for (int i = 0; i < NofLs; i++)
		{
			for (int r = 0; r < Ls[i].Size; r++)
			{

				for (int j = r - size + 1, k = 0; j <= r; j++, k++)
				{
					if ((Ls[i].Cs[j] == ch[k])or (Ls[i].Cs[j] == ch[k]-32)or (Ls[i].Cs[j]-32 == ch[k]))
					{
						match_count++;
						
					}
					else
					{
						match_count = 0;
						break;
					}
				
					if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '.')
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == '.' && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return;
					}
				}
				if (!(match_count == size))
				{
					match_count = 0;
				}
				count = 0;
			}

		}

	}
	bool MatchA_Word_All_Case_InSensitive(int& li, int& ci, string ch)
	{
		int size = Size_String(ch);
		int count = 0, match_count = 0;
		for (int i = 0; i < NofLs; i++)
		{
			for (int r = 0; r < Ls[i].Size; r++)
			{

				for (int j = r - size + 1, k = 0; j <= r; j++, k++)
				{
					if ((Ls[i].Cs[j] == ch[k]) or (Ls[i].Cs[j] == ch[k] - 32) or (Ls[i].Cs[j] - 32 == ch[k]))
					{
						match_count++;

					}
					else
					{
						
						match_count = 0;
						break;
					}

					if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '.')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == '.' && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
				}
				if (!(match_count == size))
				{
					match_count = 0;
				}
				count = 0;
			}

		}
		return false;

	}
	void Replace_First_Word(int& cc, int& cr, string replace,int Size_Word)
	{
		int size = Size_String(replace);
		for (int j=cc+Size_Word,k=0;k<Size_Word;k++)
		{
			DeleteACharAt(cr, j);			
				j--;
		}
		int ri=cc;
		for (int h = 0;ri<size+cc;ri++,h++)
		{
			InsertACharacter(cr, ri,replace[h]);
		}
	}
	
	void MatchA_Word_After_Cursor_Case_InSensitive(int& li, int& ci, string ch)
	{
		int size = Size_String(ch);
		int count = 0, match_count = 0;
		for (int i = li; i < NofLs; i++)
		{
			for (int r = ci; r < Ls[i].Size; r++)
			{

				for (int j = r - size + 1, k = 0; j <= r; j++, k++)
				{
					if (!(Ls[i].Cs[j] == ch[k]) or (Ls[i].Cs[j] == ch[k] - 32) or (Ls[i].Cs[j] - 32 == ch[k]))
					{
						match_count++;						
					}
					else
					{
						ci = 0;
						match_count = 0;
						break;
					}

					if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '.')
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return;
					}
				}
				if (!(match_count == size))
				{
					match_count = 0;
				}
				count = 0;
			}

		}

	}
	bool MatchA_Word_All_Case_InSensitive_After_Cursor(int& li, int& ci, string ch)
	{
		int size = Size_String(ch);
		int count = 0, match_count = 0;
		for (int i = li; i < NofLs; i++)
		{
			for (int r = ci; r < Ls[i].Size; r++)
			{

				for (int j = r - size + 1, k = 0; j <= r; j++, k++)
				{
					if ((Ls[i].Cs[j] == ch[k]) or (Ls[i].Cs[j] == ch[k] - 32) or (Ls[i].Cs[j] - 32 == ch[k]))
					{
						match_count++;

					}
					else
					{
						ci = 0;
						match_count = 0;
						break;
					}

					if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '.')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == '.' && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == '.' && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[r + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
				}
				
			}

		}
		return false;

	}
	
	void MatchA_Word_Previous_Cursor_Case_InSensitive(int& li, int& ci, string ch)
	{
		int size = Size_String(ch);
		bool  check = true;
		int count = 0, match_count = 0;
		for (int i = li; i >=0; i--)
		{
			
			for (int r = Ls[i].Size-1; r >=0; r--)
			{
				if (i==li && check==true)
				{
					r = ci;
					check = false;
				}
				for (int j = r-size+1, k = 0; j<=r; j++, k++)
				{
					if ((Ls[i].Cs[j] == ch[k]) or (Ls[i].Cs[j] == ch[k] - 32) or (Ls[i].Cs[j] - 32 == ch[k]))
					{
						match_count++;
					}
					else
					{
						//ci = 0;
						match_count = 0;
						break;
					}
					if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						//ci = r;
						ci = r - size+1;
						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '.')
					{
						li = i;
						//ci = r;
						ci = r - size+1;


						return;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						//ci = r;
						ci = r - size+1;

						return;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '\0')
					{
						li = i;
						//ci = r;
						ci = r - size+1;
						return;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[j + 1] == '\0')
					{
						li = i;
						//ci = r;
						ci = r - size+1;
						return;
					}
				}
				if (!(match_count == size))
				{
					match_count = 0;
				}
				count = 0;
			}

		}

	}
	bool MatchA_Word_ALLPrevious_Cursor_Case_InSensitive(int& li, int& ci, string ch)
	{
		int size = Size_String(ch);
		bool  check = true;
		int count = 0, match_count = 0;
		for (int i = li; i >= 0; i--)
		{

			for (int r = Ls[i].Size - 1; r >= 0; r--)
			{
				if (i == li && check == true)
				{
					r = ci;
					check = false;
				}
				for (int j = r - size + 1, k = 0; j <= r; j++, k++)
				{
					if ((Ls[i].Cs[j] == ch[k]) or (Ls[i].Cs[j] == ch[k] - 32) or (Ls[i].Cs[j] - 32 == ch[k]))
					{
						match_count++;
					}
					else
					{
						match_count = 0;
						break;
					}
					if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '.')
					{
						li = i;
						ci = r - size + 1;


						return true;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[j + 1] == 32)
					{
						li = i;
						ci = r - size + 1;

						return true;
					}
					else if (match_count == size && Ls[i].Cs[j - match_count] == 32 && Ls[i].Cs[j + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
					else if (match_count == size && j - match_count + 1 == 0 && Ls[i].Cs[j + 1] == '\0')
					{
						li = i;
						ci = r - size + 1;
						return true;
					}
				}
				if (!(match_count == size))
				{
					match_count = 0;
				}
				count = 0;
			}

		}

	}	
	void Regrow(char*& Ds, char value, int& Size)
	{
		char* ch = new char[Size+1];
		for (int h = 0; h < Size ; h++)
		{
			ch[h] = Ds[h];
		}
		ch[Size] = value;
		delete[] Ds;
		Ds = ch;
		Size++;
	}
	void RegrowInt(int*& Ds, int value, int Size)
	{
		int* ch = new int[Size];
		for (int h = 0; h < Size-1; h++)
		{
			ch[h] = Ds[h];
		}
		ch[Size-1] = value;
		delete[] Ds;
		Ds = ch;
	}
	
};

class TextEditor
{
	friend class Line;
	friend class Document;
private:
	int cr, cc;
	Document* ADocument;
public:
	TextEditor(const string &dname);
	void Editing();
	~TextEditor();


};

