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
import bb.cascades 1.0

// creates one page with a label
Page {
    property alias sequenceText: sequence.text
    property alias scoreText: score.text
    property alias clueText: clue.text
    property alias answerText: answer.text
    property alias answerEnable: answer.enabled
    
    Container{
        layout: StackLayout {}
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        Container {
            
            layout: DockLayout {}
            background: Color.create("#0F1000")
            minHeight: 525.0
            ImageView {
                opacity: 0.5
                id: hipster
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Right
                imageSource: "asset:///images/hispter.png"
                scalingMethod: ScalingMethod.AspectFit
            }
            TextField {
                id: answer
                inputMode: TextFieldInputMode.Text
                textStyle.fontSize: FontSize.XLarge
                textStyle.textAlign: TextAlign.Left
                backgroundVisible: false
                textStyle.color: Color.create("#ffffffff")
                hintText: "Type here for your turn"
                text: ""
                bottomMargin: 0.0
                leftMargin: 0.0
                enabled: false
                input {
                    submitKey: SubmitKey.Done
                    onSubmitted: {
                        SmartSeq.updateGame(answer.text)
                    }
                }
            }
            Label {
                id: clue
                text: "<html><div style='font-size:96pt'>?</div></html>"
                textStyle.color: Color.create("#ffffffff")
                textStyle.textAlign: TextAlign.Center
                leftPadding: 120.0
                bottomPadding: 120.0
            }
        }
        Container {        
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            Container {
                
                background: Color.create("#0F1000")
                opacity: 0.5
                layout: StackLayout {
                }
                minWidth: 540.0
                Container {
                    background: Color.create("#0F1000")
                    opacity: 0.5
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: "Sequence: "
                        textStyle.fontSize: FontSize.XLarge
                        textStyle.color: Color.create("#ffffffff")
                        verticalAlignment: VerticalAlignment.Bottom
                        textStyle.textAlign: TextAlign.Left
                    }
                    Label {
                        id: sequence
                        text: ""
                        textStyle.fontSize: FontSize.XLarge
                        textStyle.color: Color.create("#ffffffff")
	                verticalAlignment: VerticalAlignment.Bottom
	                textStyle.textAlign: TextAlign.Left
	            }
	        }
	        	Container {
	            background: Color.create("#0F1000")
	            opacity: 0.5
	            layout: StackLayout {
	                orientation: LayoutOrientation.LeftToRight
	            }
	            Label {
	                text: "Points: "
	                textStyle.fontSize: FontSize.XLarge
	                textStyle.color: Color.create("#ffffffff")
	                verticalAlignment: VerticalAlignment.Bottom
	                textStyle.textAlign: TextAlign.Left
	            }
	            Label {
	                id: score
	                text: ""
	                textStyle.fontSize: FontSize.XLarge
	                textStyle.color: Color.create("#ffffffff")
	                verticalAlignment: VerticalAlignment.Bottom
	                textStyle.textAlign: TextAlign.Left
	            }
	        }
             }
            Container{
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Bottom
                Button {
                text: "Start"
                onClicked: {
                    SmartSeq.startGame()
                }
                }
            }
        }
    }
}

