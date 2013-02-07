//
// Copyright 2013 Andres Leonardo Martinez Ortiz
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "SmartSeq.hpp"
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/system/SystemToast>
#include <QString>

using namespace bb::cascades;
using namespace bb::system;

SmartSeq::SmartSeq(bb::cascades::Application *app)
: QObject(app)
{

	// create scene document from main.qml asset
	// set parent to created document to ensure it exists for the whole application lifetime
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

	// create root object for the UI
	_root = qml->createRootObject<AbstractPane>();
	_clue_format ="<html><div style='font-size:96pt'>%1</div></html>";
	_score=0;
	_sequence = "";
	_clue = "";
	_alphabet = "abcdefghijklmnopqrstuvwyxz";
	_game = new Game();

	qml->setContextProperty("SmartSeq",this);
	_score=0;

	// set created root object as a scene
	app->setScene(_root);
}


void
SmartSeq::startGame(){

	SystemToast *toast = new SystemToast(this);
	toast->setBody("Great!\nOff we go!");
	toast->show();

	_score=0;
	_sequence = "";
	_clue = "";
	_attemps=0;

	_root->setProperty("scoreText",QString("%1 pts").arg(_score));

	_root->setProperty("answerEnable",true);

	toast->setBody("The first two characters \n of the sequence are...");
	toast->show();

	_game->reset();

	int firstIndex = _game->getNext();

	int secondIndex = _game->getNext();
	QString initialSeq = QString("%1%2").arg(_alphabet[firstIndex]).arg(_alphabet[secondIndex]);

	_sequence+=initialSeq;
	_root->setProperty("clueText",_clue_format.arg(initialSeq));
	_root->setProperty("sequenceText",_sequence);
};


void
SmartSeq::updateGame(QString answer){

	static bool bEnd=false;
	_root->setProperty("answerEnable",false);

	SystemToast *toast = new SystemToast(this);

	answer = answer.toLower();

	//check answer
	if (answer.compare(QString(_alphabet[_game->getNext()]))==0){
		if (_attemps==5){
			if (!bEnd)
				bEnd=true;
			else {
				bEnd=false;
				toast->setBody("Hooray!\n You are a smart guy...\n Start a new game to try again.");
				toast->show();

				if (_game) delete _game;
				_game = new Game();
				_score=0;
				_attemps=0;
				_sequence = "";
				_clue = "?";

				_root->setProperty("scoreText",QString("%1 pts").arg(_score));
				_root->setProperty("sequenceText",_sequence);
				_root->setProperty("clueText",_clue_format.arg(_clue));
				_root->setProperty("answerEnable",false);
				return;
			}

			toast->setBody("Ok, you got it!\n Let's try something more difficult...");
			toast->show();

			_attemps=1;
			_score+=1;
			_sequence="";
			if (_game)
				delete _game;

			_game = new EvenSeq();

			int firstIndex = _game->getNext();

			int secondIndex = _game->getNext();
			QString initialSeq = QString("%1%2").arg(_alphabet[firstIndex]).arg(_alphabet[secondIndex]);

			_sequence+=initialSeq;
			_root->setProperty("clueText",_clue_format.arg(initialSeq));
			_root->setProperty("sequenceText",_sequence);
			_root->setProperty("scoreText",QString("%1 pts").arg(_score));
		}else{
			_score+=1;
			_attemps+=1;
			_sequence += answer;
			_root->setProperty("sequenceText",_sequence);
			_root->setProperty("scoreText",QString("%1 pts").arg(_score));

			toast->setBody("Well done!\n So the next is...");
			toast->show();

			int nextIndex = _game->getNext();
			QString nextClue = QString("%1").arg(_alphabet[nextIndex]);

			_root->setProperty("clueText",_clue_format.arg(nextClue));
			_sequence+=nextClue;

			_root->setProperty("sequenceText",_sequence);
		}
		_root->setProperty("answerEnable",true);
	}else {
		toast->setBody("Opss... \n I am afraid You were wrong \n Try again from the beginning!");
		toast->show();

		_score=0;
		_attemps=0;
		_sequence = "";
		_clue = "?";

		_root->setProperty("scoreText",QString("%1 pts").arg(_score));
		_root->setProperty("sequenceText",_sequence);
		_root->setProperty("clueText",_clue_format.arg(_clue));
		_root->setProperty("answerEnable",false);
	}

	_root->setProperty("answerText","");


};
