//
//  ContentView.swift
//  SEDG-handband
//
//  Created by Rishi Kothari on 2023-08-31.
//

import SwiftUI

struct ContentView: View {
    var seizurePercent = 12
    var body: some View {
        ZStack {
            
            TabView() {
                VStack {

                }
                .tabItem {
                  Image(systemName: "circle")
                  Text("Log")
                }

                
                ZStack {
                    GeometryReader { geo in
                        Image("homeScreenBG")
                            .resizable()
                            .frame(width: geo.size.width, height:600)
                            
                    }.ignoresSafeArea(.all, edges: [.top, .leading, .trailing])
                    VStack {
                        
                        Text("Hey!")
                            .font(.largeTitle)
                            .fontWeight(.semibold)
                            .multilineTextAlignment(.leading)
                        Spacer()
                        

                        Text("Your patient has had " + String(seizurePercent) + "% less seizures this month!")
                            .multilineTextAlignment(.trailing)
                        Spacer()
                        Text("Current state of patient: ")
                            .font(.title)
                            .multilineTextAlignment(.center)
                        
                        Spacer()
                    }
                }
                .tabItem {
                  Image(systemName: "square")
                  Text("Home")
                }
                
                .tabItem {
                    Image(systemName: "pencil")
                }
                
                VStack {
                    Text("adfjbasdkfnaslkdjfnalkjsdnf.")
                }
                .tabItem {
                    Image(systemName: "triangle")
                    Text("Relax")
                }
                
                
                
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}

