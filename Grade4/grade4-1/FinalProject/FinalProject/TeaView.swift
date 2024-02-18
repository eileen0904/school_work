//
//  TeaView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/17.
//

import SwiftUI
import FirebaseFirestore
import FirebaseFirestoreSwift
import FirebaseAuth

struct TeaView: View{
    
    @EnvironmentObject var data: AllDrinks
    @FirestoreQuery var favorites: [Favorite]
    
    @State var order: Drink
    private let user_name: String
    @State var isFill = false

    @State var sizeDefault = "M"
    @State var sugarDefault = "全糖"
    @State var iceDefault = "全冰"
    
    @State var size: [String] = []
    @State var 冰度: [String] = []
    @State var 甜度: [String] = []
    
    @State private var showAlert = false
    @State private var alertTitle = ""
    
    init(order: Drink, user_name: String, isFill: Bool){
        self.order = order
        self.isFill = isFill
        self.user_name = user_name
        self._favorites = FirestoreQuery(collectionPath: "user/\(self.user_name)/favorite")
    }
    
    var body: some View{
        ZStack{
            Color(Color.wootea)
                .ignoresSafeArea()
            
            VStack(alignment: .center, spacing: 10){
                Text("\(order.name)")
                    .foregroundColor(.black)
                    .font(.custom("ZenMaruGothic-Bold", size: 40))
                    .padding(10)
                    .background(Color.newRed)
                    .cornerRadius(40)
                
                HStack(alignment: .center){
                    Image(order.name)
                        .resizable()
                        .scaledToFit()
                        .frame(width: 200, height: 300)
                    
                    VStack(alignment: .center, spacing: 20){
                        Menu{
                            ForEach(size, id: \.self){ option in
                                Button{
                                    if option == "M"{
                                        order.price = order.Mprice
                                        order.size = "M"
                                        sizeDefault = "M"
                                    } else {
                                        order.price = order.Lprice
                                        order.size = "L"
                                        sizeDefault = "L"
                                    }
                                } label: {
                                    Text(option)
                                }
                            }
                        } label: {
                            Text("大小：\(sizeDefault)")
                                .font(.custom("ZenMaruGothic-Medium", size: 20))
                                .padding(10)
                                .foregroundColor(.white)
                                .background(Color.newRed)
                                .cornerRadius(40)
                        }
                        .onAppear{
                            if(order.Mprice > 0 && order.Lprice == -1){
                                size = ["M"]
                            }
                            else if(order.Mprice < 0 && order.Lprice > 0){
                                size = ["L"]
                            }
                            else{
                                size = ["M", "L"]
                            }
                        } // menu size

                        Menu{
                            ForEach(冰度, id: \.self) { option in
                                Button {
                                    iceDefault = option
                                    order.ice = option
                                } label: {
                                    Text(option)
                                }
                            }
                        } label: {
                            Text("冰度：\(iceDefault)")
                                .font(.custom("ZenMaruGothic-Medium", size: 20))
                                .padding(10)
                                .foregroundColor(.white)
                                .background(Color.newRed)
                                .cornerRadius(40)
                        }
                        .onAppear{
                            if(order.hasHot){
                                冰度 = ["熱", "去冰", "微冰", "少冰", "全冰"]
                            }
                            else{
                                if(order.ice == "固定"){
                                    冰度 = ["固定"]
                                }
                                else{
                                    冰度 = ["去冰", "微冰", "少冰", "全冰"]
                                }
                            }
                        } // menu ice
                        
                        Menu{
                            ForEach(甜度, id: \.self) { option in
                                Button {
                                    sugarDefault = option
                                    order.sugar = option
                                } label: {
                                    Text(option)
                                }
                            }
                        } label: {
                            Text("甜度 ：\(sugarDefault)")
                                .font(.custom("ZenMaruGothic-Medium", size: 20))
                                .padding(10)
                                .foregroundColor(.white)
                                .background(Color.newRed)
                                .cornerRadius(40)
                            
                        } 
                        .onAppear{
                            if(order.sugar == "固定"){
                                甜度 = ["固定"]
                            }
                            else{
                                甜度 = ["無糖", "微糖", "半糖", "少糖", "全糖"]
                            }
                        }// menu sugar
                    } // vstack
                } // hstack
                .overlay(alignment: .bottomLeading, content: {
                    Button {
                        isFill.toggle()
                        if isFill == true{
                            modifyFav(name: order.name, isFav: true)
                        }
                        else{
                            modifyFav(name: order.name, isFav: false)
                        }
                    } label: {
                        Image(systemName: isFill ? "heart.fill" : "heart")
                            .foregroundColor(.red)
                            .font(.system(size: 35))
                    }
                })
                
                Text("\(order.description)")
                    .foregroundColor(.black)
                    .font(.custom("ZenMaruGothic-Regular", size: 20))
                    .padding()
                
                Text("金額：\(order.price) $")
                    .foregroundColor(.black)
                    .font(.custom("ZenMaruGothic-Bold", size: 30))
                
                Spacer()
                // add to order
                Button{
                    data.orders.append(order)
                    data.calTotal()
                    
                    alertTitle = "已加入訂單！"
                    showAlert = true
                } label: {
                    Text("加入訂單")
                        .font(.custom("ZenMaruGothic-Medium", size: 25))
                        .padding(10)
                        .foregroundColor(.white)
                        .background(Color.newRed)
                        .cornerRadius(40)
                }
                .alert(alertTitle, isPresented: $showAlert){
                    Button("OK") {}
                } message: {
                    Text("")
                }
            } // vstack
        } // zstack
    } // body
    
    // update favorite list in database
    func modifyFav(name: String, isFav: Bool) {
        data.modifyFavorite(user_name: user_name, name: name, isFav: isFav)
    }
}

struct TeaView_Previews: PreviewProvider {
    static var previews: some View {
        TeaView(order: Drink(name: "最完美手沖泰奶", description: "五桐號特別保留「茶：奶 ＝ 7：3」配比。加入頂級錫蘭紅茶及特調奶水與煉乳，每口都融合紅茶濃郁的茶香與淡奶的絲滑擁抱！", Mprice: 50, Lprice: 50, type: ""), user_name: "name", isFill: false)
            .environmentObject(AllDrinks())
            .environmentObject(GetData())
        
    }
}
