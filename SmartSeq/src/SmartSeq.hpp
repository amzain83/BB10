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
#ifndef SmartSeq_HPP_
#define SmartSeq_HPP_

#include <QObject>
#include <bb/cascades/AbstractPane>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class SmartSeq : public QObject
{
	Q_OBJECT
private:
	class Game{
	public:
		Game(){
			_index=-1;
		};
		int getNext(){

			if (_index<0)
				_index=0;
			else
				_index=nextIndex();

			return _index;
		};

		void reset(){
			_index=-1;
		};

	protected:
		virtual int nextIndex(){
			_index=(_index+1)%_alphabet_lenght;
			return _index;
		};

		static const int _alphabet_lenght = 26;
		int _index;
	};

	class EvenSeq: public Game{
		public:
			EvenSeq():Game(){
			};
		private:
			int nextIndex(){
				_index=(_index+2)%_alphabet_lenght;
				return _index;
			};
		};

	class OddSeq: public Game{
		public:
			OddSeq():Game(){
				_index=1;
			};
		private:
			int nextIndex(){
				_index=(_index+2)%_alphabet_lenght;
				return _index;
			};
		};
private:
	bb::cascades::AbstractPane *_root;
	long _score;
	QString _sequence;
	QString _clue;
	QString _clue_format;
	QString _alphabet;
	Game* _game;
	int _attemps;

public:
	SmartSeq(bb::cascades::Application *app);
	virtual ~SmartSeq() {if (_game) delete _game;};

	Q_INVOKABLE void startGame();

	Q_INVOKABLE void updateGame(QString answer);
};


#endif /* SmartSeq_HPP_ */
