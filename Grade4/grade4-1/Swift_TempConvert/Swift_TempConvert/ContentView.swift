//
//  ContentView.swift
//  Swift_TempConvert
//
//  Created by 張芯翎 on 2023/10/18.
//

import SwiftUI
import SwiftData

struct ContentView: View {
    @State private var inputTemp = ""
    @State private var outputTemp = ""
    @FocusState var isFocused: Bool
    
    var body: some View {
        ZStack{
            Color("Honeydew2")
                .ignoresSafeArea()
            
            VStack(spacing: 10){
                Text("溫度轉換")
                    .font(.largeTitle)
                    .fontWeight(.semibold)
                    .foregroundColor(Color.skyBlue4)
                Text("Temperature Converter")
                    .font(.largeTitle)
                    .fontWeight(.semibold)
                    .foregroundColor(Color.skyBlue4)
                TextField("輸入華氏溫度", text: $inputTemp)
                    .textFieldStyle(.roundedBorder)
                    .keyboardType(.decimalPad) // 設定鍵盤樣式
                    .focused($isFocused)
                    .padding()
                Button {
                    isFocused = false
                    if let inputF = Double(inputTemp){
                        let temp = (inputF - 32) * 5 / 9
                        outputTemp = String(format:"%.2f", temp)
                    }
                    else{
                        outputTemp = "0.00"
                    }
                } label:{
                    Text("轉換")
                        .fontWeight(.semibold)
                        .font(.title2)
                        .foregroundStyle(.white)
                }
                .padding()
                .background(Color.skyBlue4)
                .cornerRadius(40)
                Text("Temperature : \(outputTemp)°C")
                    .padding()
                    .font(.system(size: 30))
                    .fontWeight(.semibold)
                    .foregroundColor(Color.skyBlue4)
                Image("icon1")
                    .resizable()
                    .scaledToFit()
            }
            .padding()
        }
    }
}

struct ContentView_Previews: PreviewProvider{
    static var previews: some View{
        ContentView()
    }
}

