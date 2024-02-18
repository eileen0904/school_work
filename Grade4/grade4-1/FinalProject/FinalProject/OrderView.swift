//
//  OrderView.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/16.
//

import SwiftUI
import FirebaseFirestore
import FirebaseFirestoreSwift

struct OrderView: View{
    @EnvironmentObject var data: AllDrinks
    private let user_name: String
    
    @State private var showAlert = false
    @State private var alertTitle = ""
    @State var oriorder: [Drink] = []
    
    init(user_name: String){
        self.user_name = user_name
    }
    
    var body: some View{
        NavigationView{
            ZStack{
                Color(Color.wootea)
                    .ignoresSafeArea()

                VStack(spacing: 20){
                    List{
                        ForEach(data.orders.indices, id: \.self) { item in
                            HStack{
                                Image("\(data.orders[item].name)")
                                .resizable()
                                .scaledToFit()
                                .frame(width: 100, height: 100)
                                
                                VStack(alignment: .leading, spacing: 10){
                                    Text("\(data.orders[item].name)")
                                        .font(.custom("ZenMaruGothic-Medium", size: 25))
                                        .foregroundColor(.black)
                                        .multilineTextAlignment(.leading)
                                    Text("\(data.orders[item].size), \(data.orders[item].ice), \(data.orders[item].sugar)")
                                        .font(.custom("ZenMaruGothic-Medium", size: 20))
                                        .foregroundColor(.black)
                                        .multilineTextAlignment(.leading)
                                } // vstack
                                Spacer()
                                Text("$\(data.orders[item].price)")
                                    .font(.custom("ZenMaruGothic-Medium", size: 25))
                                    .foregroundColor(.black)
                                    .multilineTextAlignment(.trailing)
                            } // hstack
                            .onAppear{
                                oriorder = data.orders
                            }
                        } // for each
                        .onDelete{ indexSet in
                            data.orders.remove(atOffsets: indexSet)
                            // store original all id
                            var ori = [String]()
                            var new = [String]()
                            
                            for i in oriorder.indices {
                                ori.append(oriorder[i].id!)
                            }
                            for i in data.orders.indices {
                                new.append(data.orders[i].id!)
                            }
                            
                            for i in missElement(arrayA: ori, arrayB: new) {
                                deleteData(id: i)
                            }
                            data.calTotal()
                        }
                        .listRowSeparatorTint(.black)
                    } // list
                    .listStyle(.plain)
                    
                    Text("Total : \(data.total) $")
                        .foregroundColor(.black)
                        .font(.custom("ZenMaruGothic-Bold", size: 30))
                    
                    Spacer()
                    
                    Button{
                        if data.orders.isEmpty {
                            alertTitle = "您的訂單是空的"
                        }
                        showAlert = true
                        
                        for drink in data.orders {
                            createOrder(drink: drink)
                            alertTitle = "已完成下單！"
                        }
                        data.removeOrder()
                    } label: {
                        Text("下單")
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
        } // nav
    } // body
    
    // create order to firestore
    func createOrder(drink: Drink) {
        let db = Firestore.firestore()
        do{
            let documentReference = try db.collection("user").document(user_name).collection("order").addDocument(from: drink)
                    print(documentReference.documentID)
        } catch {
            print(error)
        }
    }
    
    func missElement(arrayA: [String], arrayB: [String]) -> Set<String>{
        let setA = Set(arrayA)
        let setB = Set(arrayB)

        return setA.subtracting(setB)
    }
    
    func deleteData(id: String) {
        let db = Firestore.firestore()
        let documentReference = db.collection("order").document(id)
        documentReference.delete()
    }
}

struct OrderView_Previews: PreviewProvider {
    static var previews: some View {
        OrderView(user_name: "name")
            .environmentObject(AllDrinks())
            .environmentObject(GetData())
    }
}
