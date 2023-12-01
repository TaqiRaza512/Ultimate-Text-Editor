#include<fstream>
#include "TextEditor.h"
#include<iostream>

#include<Windows.h>
#include<cmath>
#include<conio.h>

using namespace std;
struct Word
{
	int size=0;
	int* NoC;
	char* Ds;
	string word;

};
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}



TextEditor::TextEditor(const string &dname)
{

	ADocument = new Document(dname);
	ADocument->PrintDocument();
}
void Menu()
{
	cout << "\n\tPress CNTRL+S+D to save a file.\n";
	cout << "\n\tPress CNTRL+S+W for the menu of shortcuts.\n";
	cout << "\n\tPress CNTRL+S+Q to quite the file without saving.\n";
	cout << "\n\tPress CNTRL+S+U to convert the file where cursor points to Capital letters.\n";
	cout << "\n\tPress CNTRL+S+I to convert the file where cursor points to Lower letters.\n";
	cout << "\n\tPress CNTRL+S+X to find the word sensitive.\n";
	cout << "\n\tPress CNTRL+S+N to find the word Insensitive.\n";
	cout << "\n\tPress CNTRL+S+B to Replace the first word.\n";
	cout << "\n\tPress CNTRL+S+P to Replace all word.\n";
	cout << "\n\tPress CNTRL+S+Y to add prefix to word.\n";
	cout << "\n\tPress CNTRL+S+O to add Post to word.\n";
	cout << "\n\tPress CNTRL+S+V to find the average word length.\n";
	cout << "\n\tPress CNTRL+S+K to find the sub-word.\n";
	cout << "\n\tPress CNTRL+S+E to find the Sentence.\n";
	cout << "\n\tPress CNTRL+S+J to find the Numbers of Special Characters.\n";
	cout << "\n\tPress CNTRL+S+G to find the Numbers of Sentences.\n";
	cout << "\n\tPress CNTRL+S+T for substring count.\n";
	cout << "\n\tPress CNTRL+S+L to find the largest word.\n";
	cout << "\n\tPress CNTRL+S+Z to find the Smallest word length.\n";
	cout << "\n\tPress CNTRL+S+R to find the the largest paragragh length.\n";
	cout << "\n\tPress CNTRL+S+H to replace the next in the file.\n";
	cout << "\n\tPress CNTRL+f1 to replace all the next word in the file.\n";
	cout << "\n\tPress CNTRL+f2 to replace previous word in the file.\n";
	cout << "\n\tPress CNTRL+f3 to replace all previous word in the file.\n";
	cout << "\n\tPress CNTRL+f4 to find the biggest of all the other word in the file.\n";


}
void TextEditor::Editing()
{
	Line ALine;
	int d;
	char ch;
	cr = 0, cc = 0;
	gotoRowCol(cr, cc);
	while (true)
	{
		if (_kbhit())
		{
			d = _getch();
			if (d == 224)
			{
				d = _getch();
				if (d == 72)
				{
					if (cr > 0)
					{
						cr--;
					}
					if (ADocument->Ls[cr].Size < cc)
					{
						cc = ADocument->Ls[cr].Size;
					}
				}
				else if (d == 80)
				{
					if (ADocument->NofLs - 1 != cr)
					{
						cr++;
					}
					if (ADocument->Ls[cr].Size < cc)
					{
						cc = ADocument->Ls[cr].Size;
					}
				}
				else if (d == 77)
				{
					if (cr != ADocument->NofLs)
					{
						cc++;
						if (cc == ADocument->Ls[cr].Size + 1)
						{
							cc = 0;
							cr++;
						}
					}
				}
				else if (d == 75)
				{
					cc--;
					if (cc == -1)
					{
						cr--;
						cc = ADocument->Ls[cr].Size;
					}
				}
				gotoRowCol(cr, cc);

				ADocument->PrintDocument();

			}
			else if (d == 8)
			{
				if (cr >= 0)
				{

					if (cc == 0 && cr != 0)
					{

						cc = ADocument->Ls[cr - 1].Size;
						ADocument->MergeTheLine(cr, cc);
						cr--;
					}
					else
					{
						ADocument->DeleteACharAt(cr, cc);
						cc--;
					}
					ADocument->PrintDocument();

				}

			}
			else if (d == 13)
			{
				ADocument->InsertANewLineAt(cr, cc);
				cr++;
				cc = 0;
				ADocument->PrintDocument();
			}
			else if (d == 24)
			{
				ADocument->PrintDocumentFile();
			}
			else if (d == 19)
			{
				d = _getch();
				if (d == 4)
				{
					ADocument->PrintDocument();
					ADocument->PrintDocumentFile();
					cout << "\tFILE SAVED SUCCESSFULLY..........";
					char ch = _getch();
				}
				else if (d == 17)
				{
					break;
				}
				else if (d == 21)
				{
					/*convert the word where cursor points to upper*/

					ADocument->TO_Upper(cr, cc);
					ADocument->PrintDocument();

				}
				else if (d == 9)
				{
					/*convert the word where cursor points to lower*/
					ADocument->TO_Lower(cr, cc);
					ADocument->PrintDocument();

				}
				else if (d == 24)
				{
					/*case sensitive word finding*/

					string ch;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> ch;
					ADocument->MatchA_Word_Case_Sensitive(cr, cc, ch);
					ADocument->PrintDocument();

				}
				else if (d == 14)
				{
					/*case Insensitive word finding*/

					string ch;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> ch;
					ADocument->MatchA_Word_Case_InSensitive(cr, cc, ch);
					ADocument->PrintDocument();

				}
				else if (d == 23)
				{
					system("cls");
					Menu();
					char ch = _getch();
					ADocument->PrintDocument();
				}
				else if (d == 2)
				{
					/*Replace first word */
					string word, replace;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> word;
					ADocument->MatchA_Word_Case_Sensitive(cr, cc, word);
					cout << "\nplease enter the replacement for a word : ";
					cin >> replace;
					int Size_Word = ADocument->Size_String(word);
					ADocument->Replace_First_Word(cc, cr, replace, Size_Word);
					ADocument->PrintDocument();
				}
				else if (d == 16)
				{
					/*control+P*/
					string word, replace;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> word;
					cout << "\nplease enter the replacement for a word : ";
					cin >> replace;
					int Size_Word = ADocument->Size_String(word);

					while (cr <= ADocument->NofLs - 1 or cc <= ADocument->Ls[ADocument->NofLs - 1].Size - 1)
					{
						bool check = ADocument->MatchA_Word_All_Case_InSensitive(cr, cc, word);
						if (check == true)
						{
							ADocument->Replace_First_Word(cc, cr, replace, Size_Word);
						}
						else
						{
							break;
						}
					}
					ADocument->PrintDocument();
				}
				else if (d == 25)
				{
					/*Pre_Fix*/
					string word, Prefix;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> word;
					cout << "\nplease enter prefix to word : ";
					cin >> Prefix;
					int Size_Word = ADocument->Size_String(word);
					int Size_Prefix = ADocument->Size_String(Prefix);
					while (true)
					{
						bool check = ADocument->MatchA_Word_All_Case_InSensitive(cr, cc, word);
						if (check == true)
						{
							for (int ci = cc, i = 0; i < Size_Prefix; i++, ci++)
							{
								ADocument->InsertACharacter(cr, ci, Prefix[i]);
							}
						}
						else
						{
							break;
						}
					}
					ADocument->PrintDocument();
				}
				else if (d == 15)
				{
					/*Post_Fix*/
					string word, Prefix;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> word;
					cout << "\nplease enter prefix to word : ";
					cin >> Prefix;
					int Size_Word = ADocument->Size_String(word);
					int Size_Prefix = ADocument->Size_String(Prefix);

					while (true)
					{
						bool check = ADocument->MatchA_Word_All_Case_InSensitive(cr, cc, word);
						if (check == true)
						{
							for (int ci = cc + Size_Word, i = 0; i < Size_Prefix; i++, ci++)
							{
								ADocument->InsertACharacter(cr, ci, Prefix[i]);
							}
						}
						else
						{
							break;
						}
					}
					ADocument->PrintDocument();
				}
				else if (d == 22)
				{
					/*Avergae Word  Length*/
					int count = 0, characters = 0;

					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{

							if (ADocument->Ls[ri].Cs[ci] == ' ' or ADocument->Ls[ri].Cs[ci] == '.')
							{
								count++;
							}
							characters++;
						}

					}
					system("cls");
					cout << "Hence the Average word length is : " << characters / count;
					char ch = _getch();
					ADocument->PrintDocument();

				}
				else if (d == 11)
				{
					/*Finding a Subword*/
					system("cls");

					char ch[1000];
					cout << "please enter any substring you want to search in the file : ";
					cin.getline(ch, 1000);
					int count = 0;
					int size = ADocument->Size_String(ch);
					bool tocont = true;
					cout << endl;
					cout << size;

					for (int ri = 0; ri < ADocument->NofLs && tocont == true; ri++)
					{
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{
							count = 0;
							for (int j = 0, col = ci; j < size; j++, col++)
							{
								if (ch[j] == ADocument->Ls[ri].Cs[col])
								{
									count++;
								}
							}
							if (count == size)
							{
								cr = ri;
								cc = ci;
								tocont == false;
								break;
							}
						}
					}
					ADocument->PrintDocument();
				}
				else if (d == 5)
				{
					/*Finding a sentence.*/
					system("cls");

					char ch[1000];
					cout << "please enter any sentence you want to search in the file : ";
					cin.getline(ch, 1000);
					int count = 0;
					int size = ADocument->Size_String(ch);
					bool tocont = true, endline = false;

					for (int ri = 0; ri < ADocument->NofLs && tocont == true; ri++)
					{
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{
							count = 0;
							for (int j = 0, col = ci; j < size; j++, col++)
							{
								if (ch[j] == ADocument->Ls[ri].Cs[col])
								{
									count++;

									if (col == ADocument->Ls[ri].Size - 1)
									{
										int match = col, end_comma = 0;

										while (ADocument->Ls[ri].Cs[match] != '.')
										{
											end_comma++;
											match--;
										}
										if (count == end_comma)
										{
											ri++;
											endline = true;
											col = -1;
										}
									}
								}
							}
							if (count == size)
							{
								if (endline == true)
								{
									cr = ri - 1;

								}
								else
								{
									cr = ri;
								}
								cc = ci;
								tocont = false;
								break;
							}

						}
					}
					ADocument->PrintDocument();
				}
				else if (d == 10)
				{
					/*Special Characters*/
					int count = 0, characters = 0;

					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{

							if (!(isalpha(ADocument->Ls[ri].Cs[ci]) or isdigit(ADocument->Ls[ri].Cs[ci])))
							{
								count++;
							}
						}
					}
					system("cls");
					cout << "Hence the number of special characters are : " << count;
					cout << "\nPress any key to continue ....\n";
					char ch = _getch();
					ADocument->PrintDocument();
				}
				else if (d == 7)
				{
					/*No of sentences*/
					int count = 0;
					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{
							if (ADocument->Ls[ri].Cs[ci] == '.')
							{
								count++;
							}
						}
					}
					system("cls");

					cout << "\nHence the number of sentences are : " << count << endl;
					cout << "Press any key to continue......\n";
					char ch = _getch();
					ADocument->PrintDocument();
				}
				else if (d == 20)
				{
					/*Substring count*/
					system("cls");
					char ch[1000];
					cout << "please enter any substring you want to count in the file : ";
					cin.getline(ch, 1000);
					int count = 0;
					int size = ADocument->Size_String(ch);
					int substring = 0;
					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{
							count = 0;
							for (int j = 0, col = ci; j < size; j++, col++)
							{
								if (ch[j] == ADocument->Ls[ri].Cs[col])
								{
									count++;
								}
							}
							if (count == size)
							{
								cr = ri;
								cc = ci;
								substring++;
							}
						}
					}
					cout << "hence the total number of substring you entered appeared in the file " << substring;
					cout << "\nPress any key to continue.....";
					char c = _getch();
					gotoRowCol(cr, cc);
					ADocument->PrintDocument();


				}
				else if (d == 12)
				{
					/*Largest Word Length*/
					int word_length = 0, Largest_word = 0, paragragh = 0;
					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						if (ADocument->Ls[ri].Size == 0)
						{
							paragragh++;
						}
						else
						{

							word_length = 0;
							for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
							{


								if (!(ADocument->Ls[ri].Cs[ci] == ' ' or ADocument->Ls[ri].Cs[ci] == '.'))
								{
									word_length++;
								}
								else
								{
									if (word_length > Largest_word)
									{
										Largest_word = word_length;

									}
									word_length = 0;
								}
							}
						}
					}


					system("cls");
					cout << "Hence the largest word length is : " << Largest_word <<
						endl << "Hence the number of paragraphs are : " << ++paragragh << endl;

					cout << "\nPress any key to continue....\n";
					char ch = _getch();
					ADocument->PrintDocument();
				}
				else if (d == 26)
				{
					/*Smallest Word Length*/
					int word_length = 0, Smallest_word = 10;
					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						word_length = 0;
						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
						{

							if (!(ADocument->Ls[ri].Cs[ci] == ' ' or ADocument->Ls[ri].Cs[ci] == '.'))
							{
								word_length++;
							}
							else
							{
								if (word_length < Smallest_word)
								{
									Smallest_word = word_length;

								}
								word_length = 0;
							}
						}
					}
					system("cls");
					cout << "Hence the Smallest word length is : " << Smallest_word;
					cout << "\nPress any key to continue....\n";
					char ch = _getch();
					ADocument->PrintDocument();
				}
				
				else if (d == 8)
				{
					/*Replace first word after the cursor ...*/
					string word, replace;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> word;
					ADocument->MatchA_Word_After_Cursor_Case_InSensitive(cr, cc, word);
					cout << "\nplease enter the replacement for a word : ";
					cin >> replace;
					int Size_Word = ADocument->Size_String(word);
					ADocument->Replace_First_Word(cc, cr, replace, Size_Word);
					ADocument->PrintDocument();

				}
			}
			else if (d == 0)
			{
				char ch = _getch();
				if (ch == 94)
				{
					Menu();
					/*Next all replace */
					string word, replace;
					system("cls");
					cout << "\nplease enter word you want to research : ";
					cin >> word;
					cout << "\nplease enter the replacement for a word : ";
					cin >> replace;
					int Size_Word = ADocument->Size_String(word);

					while (cr <= ADocument->NofLs - 1 or cc <= ADocument->Ls[ADocument->NofLs - 1].Size - 1)
					{
						bool check = ADocument->MatchA_Word_All_Case_InSensitive_After_Cursor(cr, cc, word);
						if (check == true)
						{
							ADocument->Replace_First_Word(cc, cr, replace, Size_Word);
						}
						else
						{
							break;
						}
					}
					ADocument->PrintDocument();

				}
				else if (ch == 95)
				{
					string word, replace;
					system("cls");
					cout << "\nplease enter word you want to search : ";
					cin >> word;
					ADocument->MatchA_Word_Previous_Cursor_Case_InSensitive(cr, cc, word);
					cout << "\nplease enter the replacement for a word : ";
					cin >> replace;
					int Size_Word = ADocument->Size_String(word);
					ADocument->Replace_First_Word(cc, cr, replace, Size_Word);
					ADocument->PrintDocument();
				}
				else if (ch == 96)
				{
					string word, replace;
					system("cls");
					cout << "\nplease enter word you want to research : ";
					cin >> word;
					cout << "\nplease enter the replacement for a word : ";
					cin >> replace;
					int Size_Word = ADocument->Size_String(word);

					while (cr <= ADocument->NofLs - 1 or cc <= ADocument->Ls[ADocument->NofLs - 1].Size - 1)
					{
						bool check = ADocument->MatchA_Word_ALLPrevious_Cursor_Case_InSensitive(cr, cc, word);
						if (check == true)
						{
							ADocument->Replace_First_Word(cc, cr, replace, Size_Word);
						}
						else
						{
							break;
						}

					}
					//char ch = _getch();
					ADocument->PrintDocument();
				}
//				else if (ch == 97)
//				{
//					ifstream Rdr(ADocument->DName);
//					Word BiggestWord;
//					Word SingleWord;
//					string HavingMaxWords;
//
//					Rdr >> BiggestWord.word;
//					int NoFMaxWords = 0;
//					int NoFMaxWords_record = 0;
//
//
//					Rdr.ignore();
//					for (int ri = 0; ri < ADocument->NofLs; ri++)
//					{
//						for (int ci = 0; ci < ADocument->Ls[ri].Size; ci++)
//						{
//
//							Rdr >> BiggestWord.word;
//							NoFMaxWords = 0;
//							BiggestWord.size = BiggestWord.word.size();
//							ci = ci + BiggestWord.size;
//							if (BiggestWord.word[BiggestWord.size - 1] == '.')
//							{
//								BiggestWord.word[BiggestWord.size - 1] = '\0';
//								BiggestWord.size--;
//							}
//							int size = 1;
//							BiggestWord.Ds = new char[size];
//							BiggestWord.NoC = new int[size] {};
//							BiggestWord.Ds[0] = BiggestWord.word[0];
//							BiggestWord.NoC[0]++;
//							for (int j = 1; j < BiggestWord.size; j++)
//							{
//								bool IsPresent = true;
//
//								for (int i = 0; i < size; i++)
//								{
//									if (BiggestWord.word[j] == BiggestWord.Ds[i])
//									{
//										IsPresent = false;
//										BiggestWord.NoC[i]++;
//										break;
//									}
//								}
//								if (IsPresent == true)
//								{
//									ADocument->Regrow(BiggestWord.Ds, BiggestWord.word[j], size);
//									ADocument->RegrowInt(BiggestWord.NoC, 1, size);
//								}
//
//							}
//							BiggestWord.Ds[size] = '\0';
//
//							for (int a = 0; a < ADocument->NofLs; a++)
//							{
//								bool IsNewWord = false;
//								char* WORD = new char[0];
//								SingleWord.size = 0;
//								IsNewWord = false;
//
//								for (int b = 0; b < ADocument->Ls[a].Size; b++)
//								{
//									if (IsNewWord == true)
//									{
//										IsNewWord = false;
//										WORD = nullptr;
//										WORD = new char[0];
//
//										SingleWord.size = 0;
//									}
//									if (ADocument->Ls[a].Cs[b] != '.' && ADocument->Ls[a].Cs[b] != ' ' && ADocument->Ls[a].Cs[b] != ADocument->Ls[a].Size)
//									{
//										ADocument->Regrow(WORD, ADocument->Ls[a].Cs[b], SingleWord.size);
//									}
//									else
//									{
//										IsNewWord = true;
//										WORD[SingleWord.size] = '\0';
//										int SingleSize = 1;
//										SingleWord.Ds = new char[SingleSize];
//										SingleWord.NoC = new int[SingleSize] {};
//										SingleWord.Ds[0] = WORD[0];
//										SingleWord.NoC[0]++;
//										int countChar = 0;
//										for (int j = 1; j <= SingleWord.size; j++)
//										{
//											bool IsPresent = true;
//
//											for (int i = 0; i < size; i++)
//											{
//												if (WORD[j] == SingleWord.Ds[i])
//												{
//													IsPresent = false;
//													SingleWord.NoC[i]++;
//													break;
//												}
//											}
//											if (IsPresent == true)
//											{
//												ADocument->Regrow(SingleWord.Ds, WORD[j], SingleSize);
//												ADocument->RegrowInt(SingleWord.NoC, 1, SingleSize);
//											}
//										}
//										SingleWord.Ds[SingleSize] = '\0';
//										for (int j = 0; j < SingleSize; j++)
//										{
//											for (int g = 0; g < size; g++)
//											{
//												if (BiggestWord.Ds[g] == SingleWord.Ds[j])
//												{
//													if (SingleWord.NoC[j] <= BiggestWord.NoC[g])
//													{
//														countChar++;
//														break;
//													}
//												}
//											}
//										}
//										if (countChar == SingleSize)
//										{/*
//											system("cls");
//											cout << WORD;
//											Sleep(2000);*/
//											NoFMaxWords++;
//
//										}
//										WORD = nullptr;
//										SingleWord.Ds = nullptr;
//										SingleWord.NoC = nullptr;
//									}
//								}
//							}
//
//							if (NoFMaxWords_record < NoFMaxWords)
//							{
//								NoFMaxWords_record = NoFMaxWords;
//								HavingMaxWords = BiggestWord.word;
//							}
//							BiggestWord.Ds = nullptr;
//							BiggestWord.NoC = nullptr;
//						}
//					}
//
//					system("cls");
//					cout << "Pressed";
//					//===========================For the biggest word======================
//					system("cls");
//					BiggestWord.word = HavingMaxWords;
//					int size = 1;
//					BiggestWord.Ds = new char[size];
//					BiggestWord.NoC = new int[size] {};
//					BiggestWord.Ds[0] = BiggestWord.word[0];
//					BiggestWord.NoC[0]++;
//					for (int j = 1; j <= BiggestWord.size; j++)
//					{
//						bool IsPresent = true;
//
//						for (int i = 0; i < size; i++)
//						{
//							if (BiggestWord.word[j] == BiggestWord.Ds[i])
//							{
//								IsPresent = false;
//								BiggestWord.NoC[i]++;
//								break;
//							}
//						}
//						if (IsPresent == true)
//						{
//							ADocument->Regrow(BiggestWord.Ds, BiggestWord.word[j], size);
//							ADocument->RegrowInt(BiggestWord.NoC, 1, size);
//						}
//
//					}
//					BiggestWord.Ds[size] = '\0';
//					
//					for (int a = 0; a < ADocument->NofLs; a++)
//					{
//						bool IsNewWord = false;
//						char* WORD = new char[0];
//						SingleWord.size = 0;
//						IsNewWord = false;
//
//						for (int b = 0; b <= ADocument->Ls[a].Size; b++)
//						{
//							if (IsNewWord == true)
//							{
//								IsNewWord = false;
//								WORD = nullptr;
//								WORD = new char[0];
//
//								SingleWord.size = 0;
//							}
//							if (ADocument->Ls[a].Cs[b] != '.' && ADocument->Ls[a].Cs[b] != ' ' && ADocument->Ls[a].Cs[b] != '\0')
//							{
//								ADocument->Regrow(WORD, ADocument->Ls[a].Cs[b], SingleWord.size);
//							}
//							else
//							{
//								IsNewWord = true;
//								WORD[SingleWord.size] = '\0';
//								int SingleSize = 1;
//								SingleWord.Ds = new char[SingleSize];
//								SingleWord.NoC = new int[SingleSize] {};
//								SingleWord.Ds[0] = WORD[0];
//								SingleWord.NoC[0]++;
//								int countChar = 0;
//								for (int j = 1; j < SingleWord.size; j++)
//								{
//									bool IsPresent = true;
//
//									for (int i = 0; i < size; i++)
//									{
//										if (WORD[j] == SingleWord.Ds[i])
//										{
//											IsPresent = false;
//											SingleWord.NoC[i]++;
//											break;
//										}
//									}
//									if (IsPresent == true)
//									{
//										ADocument->Regrow(SingleWord.Ds, WORD[j], SingleSize);
//										ADocument->RegrowInt(SingleWord.NoC, 1, SingleSize);
//									}
//								}
//								SingleWord.Ds[SingleSize] = '\0';
//								for (int j = 0; j <= SingleSize; j++)
//								{
//									for (int g = 0; g < size; g++)
//									{
//										if (BiggestWord.Ds[g] == SingleWord.Ds[j])
//										{
//											if (SingleWord.NoC[j] <= BiggestWord.NoC[g])
//											{
//												countChar++;
//												break;
//											}
//										}
//									}
//								}
//								if (countChar == SingleSize)
//								{
//									cout << WORD<<endl;
////									NoFMaxWords++;
//
//								}
//								WORD = nullptr;
//								SingleWord.Ds = nullptr;
//								SingleWord.NoC = nullptr;
//							}
//						}
//						char ch = _getch();
//					}
//				}
				else if (ch==98)
				{
					ofstream rdr("Code.txt");
					//==========Decoding=============
					for (int ri=0;ri<ADocument->NofLs;ri++)
					{
						for (int ci=0;ci<=ADocument->Ls[ri].Size;ci++)
						{
							rdr << char(ADocument->Ls[ri].Cs[ci] + 2);

						}
						cout << endl;
					}
					rdr.close();
					
					ifstream read("Code.txt");
					system("cls");
					char ch;
					for (int ri = 0; ri < ADocument->NofLs; ri++)
					{
						for (int ci = 0; ci <= ADocument->Ls[ri].Size; ci++)
						{
							read >> ch;
							cout << ch;
						}
					}
					char g = _getch();
				}
				else if (ch == 99)
				{
					string  decodefile;
					char ch;
					system("cls");
					cout << "\n which file you want to decode : ";
					cin >> decodefile;
					ifstream rdr(decodefile);
					while (!rdr.eof())
					{
						rdr >> ch;
						if (!(char(ch-2) == '\0'))
						{
							cout << char(ch - 2);
						}
						else
						{
							cout << endl;
						}
					}
				}
				else
				{
					ch = char(d);
					ADocument->InsertACharacter(cr, cc, ch);
					ADocument->PrintDocument();
					cc++;
				}
				gotoRowCol(cr, cc);
			}
			gotoRowCol(cr, cc);
		}
		
	}
}
TextEditor::~TextEditor()
{

}
