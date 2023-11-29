//
//  ContentView.swift
//  Swift_Conuter_Control
//
//  Created by 張芯翎 on 2023/10/18.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    @StateObject var viewModel = CounterViewModel()
    
    var body: some View {
        ZStack{
            Color("AntiqueWhite1")
                .ignoresSafeArea()
            
            VStack {
                Text("\(viewModel.counter)")
                    .fontWeight(.semibold)
                    .font(.largeTitle)
                    .padding()
                    .background(
                        LinearGradient(gradient: Gradient(colors: [Color.red, Color.blue]),
                                       startPoint: .leading, endPoint: .trailing))
                    .cornerRadius(10)
                HStack {
                    Button{
                        viewModel.increase()
                    } label:{
                        Text("Increase")
                            .fontWeight(.semibold)
                            .font(.title2)
                            .foregroundStyle(.white)
                    }
                    .padding()
                    .background(Color.green)
                    .cornerRadius(40)

                    Button {
                        viewModel.decrease()
                    } label:{
                        Text("Decrease")
                            .fontWeight(.semibold)
                            .font(.title2)
                            .foregroundStyle(.white)
                    }
                    .padding()
                    .background(Color.red)
                    .cornerRadius(40)
                    
                    Button {
                        viewModel.reset()
                    } label:{
                        Text("Reset")
                            .fontWeight(.semibold)
                            .font(.title2)
                            .foregroundStyle(.white)
                    }
                    .padding()
                    .background(Color.blue)
                    .cornerRadius(40)
                }
                .padding()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            //.environmentObject(CounterViewModel())
    }
}
